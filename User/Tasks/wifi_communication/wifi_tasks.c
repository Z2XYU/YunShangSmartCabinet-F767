#include "wifi_tasks.h"
#include "wifi_comm.h"
#include "esp8266.h"
#include <stdio.h>

/* 外部变量声明 ---------------------------------------------------------- */
extern volatile uint8_t wifi_rx_buf[256]; // WiFi UART 接收缓冲区
extern UART_HandleTypeDef huart2;         // USART2 句柄
extern DMA_HandleTypeDef hdma_usart2_rx;  // USART2 RX DMA 句柄

/* 消息队列句柄 ---------------------------------------------------------- */
osMessageQueueId_t wifiRecvQueueHandle; // WiFi 接收消息队列
const osMessageQueueAttr_t wifiRecvQueue_attributes = {
    .name = "wifiRecvQueue",
};

osMessageQueueId_t wifiSendQueueHandle; // WiFi 发送消息队列
const osMessageQueueAttr_t wifiSendQueue_attributes = {
    .name = "wifiSendQueue",
};

/* 互斥锁句柄 ------------------------------------------------------------ */
osMutexId_t wifiStateMutex; // WiFi 状态互斥锁（防止多任务竞争访问 WiFi 状态）

/* 任务句柄与属性 -------------------------------------------------------- */
osThreadId_t wifiRecvTaskHandle; // 接收任务
const osThreadAttr_t wifiRecvTask_attributes = {
    .name = "wifiRecvTask",
    .stack_size = 128 * 8, // 1KB 堆栈
    .priority = (osPriority_t)osPriorityHigh,
};

osThreadId_t wifiSendTaskHandle; // 发送任务
const osThreadAttr_t wifiSendTask_attributes = {
    .name = "wifiSendTask",
    .stack_size = 128 * 8, // 1KB 堆栈
    .priority = (osPriority_t)osPriorityHigh,
};

osThreadId_t wifiMonitorTaskHandle; // WiFi 状态监控任务
const osThreadAttr_t wifiMonitorTask_attributes = {
    .name = "wifiMonitorTask",
    .stack_size = 128 * 4, // 512B 堆栈
    .priority = (osPriority_t)osPriorityNormal,
};

/* WiFi 通信任务初始化 --------------------------------------------------- */
void wifi_communication_task_init(void)
{
    wifiStateMutex = osMutexNew(NULL); // 创建互斥锁
    // 创建接收队列（最多缓存 10 条 WifiMessage_t 消息）
    wifiRecvQueueHandle = osMessageQueueNew(10, sizeof(WifiMessage_t), &wifiRecvQueue_attributes);
    // 创建发送队列（最多缓存 10 条 WifiCommand_t 命令）
    wifiSendQueueHandle = osMessageQueueNew(10, sizeof(WifiCommand_t), &wifiSendQueue_attributes);

    // 创建任务
    wifiMonitorTaskHandle = osThreadNew(wifiMonitorTask, NULL, &wifiMonitorTask_attributes);
    wifiRecvTaskHandle = osThreadNew(wifiRecvTask, NULL, &wifiRecvTask_attributes);
    wifiSendTaskHandle = osThreadNew(wifiSendTask, NULL, &wifiSendTask_attributes);
}

/* WiFi 状态监控任务 ----------------------------------------------------- */
void wifiMonitorTask(void *argument)
{
    // 初始化 WiFi 模块，配置 SSID 和密码
    wifi_init("zhongxu", "18568601031");

    WifiState_t wifi_state = {0};

    while (1)
    {
        osMutexAcquire(wifiStateMutex, osWaitForever);
        wifi_state = wifi_get_status();
        osMutexRelease(wifiStateMutex);

        switch (wifi_state.status)
        {
        case WL_CONNECTED: // 已连接
            printf("WiFi 已连接: %s\n", wifi_state.ssid);
            wifi_status_update(); // 上报 WiFi 状态
            osDelay(10000);       // 10 秒轮询
            break;

        case WL_DISCONNECTED:   // 断开连接
        case WL_CONNECT_FAILED: // 连接失败
        case WL_WRONG_PASSWORD: // 密码错误
            printf("WiFi 未连接，尝试重连...\n");
            wifi_connect();       // 尝试重连
            osDelay(5000);        // 等待 5 秒
            wifi_status_update(); // 更新一次状态
            break;

        case WL_IDLE_STATUS:     // 空闲状态
        case WL_SCAN_COMPLETED:  // 扫描完成
        case WL_NO_SSID_AVAIL:   // 无 SSID
        case WL_CONNECTION_LOST: // 丢失连接
        case WL_NO_SHIELD:       // 无 WiFi 模块
        default:
            osDelay(2000); // 休眠 2 秒后继续检测
            break;
        }
    }
}

/* WiFi 接收任务 --------------------------------------------------------- */
void wifiRecvTask(void *argument)
{
    WifiMessage_t msg = {0};

    // 开启 USART2 DMA 空闲中断接收模式
    HAL_UARTEx_ReceiveToIdle_DMA(&huart2, wifi_rx_buf, sizeof(wifi_rx_buf));
    __HAL_DMA_DISABLE_IT(&hdma_usart2_rx, DMA_IT_HT); // 禁止半传输中断，避免干扰

    while (1)
    {
        // 阻塞等待接收队列中的数据
        if (osMessageQueueGet(wifiRecvQueueHandle, &msg, NULL, osWaitForever) == osOK)
        {
            wifi_recv_msg_handle(&msg); // 解析并处理接收到的 WiFi 消息
        }
    }
}

/* WiFi 发送任务 --------------------------------------------------------- */
void wifiSendTask(void *argument)
{
    WifiCommand_t cmd = {0};

    while (1)
    {
        // 阻塞等待发送队列中的命令
        if (osMessageQueueGet(wifiSendQueueHandle, &cmd, NULL, osWaitForever) == osOK)
        {
            wifi_send_message_handle(&cmd); // 处理并发送命令到 WiFi 模块
            printf("发送命令\n");
        }
    }
}
