#include "wifi_tasks.h"
#include "wifi_comm.h"
#include "esp8266.h"
#include <stdio.h>
#include "mqtt_message.h"

/* 外部变量声明 ---------------------------------------------------------- */
extern uint8_t wifi_rx_buf[256];         
extern UART_HandleTypeDef huart2;        
extern DMA_HandleTypeDef hdma_usart2_rx; 

/* 消息队列句柄 ---------------------------------------------------------- */
osMessageQueueId_t wifiRecvQueueHandle; 
const osMessageQueueAttr_t wifiRecvQueue_attributes = {
    .name = "wifiRecvQueue",
};

osMessageQueueId_t wifiSendQueueHandle; 
const osMessageQueueAttr_t wifiSendQueue_attributes = {
    .name = "wifiSendQueue",
};

/* 互斥锁句柄 ------------------------------------------------------------ */
osMutexId_t wifiStateMutex; 

/* 任务句柄与属性 -------------------------------------------------------- */
osThreadId_t wifiRecvTaskHandle; 
const osThreadAttr_t wifiRecvTask_attributes = {
    .name = "wifiRecvTask",
    .stack_size = 128 * 12, 
    .priority = (osPriority_t)osPriorityHigh,
};

osThreadId_t wifiSendTaskHandle; 
const osThreadAttr_t wifiSendTask_attributes = {
    .name = "wifiSendTask",
    .stack_size = 128 * 12, 
    .priority = (osPriority_t)osPriorityHigh,
};


/* WiFi 通信任务初始化 --------------------------------------------------- */
void wifi_communication_tasks_init(void)
{
    wifiStateMutex = osMutexNew(NULL); 

    wifiRecvQueueHandle = osMessageQueueNew(10, sizeof(WifiMessage_t), &wifiRecvQueue_attributes);

    wifiSendQueueHandle = osMessageQueueNew(10, sizeof(WifiCommand_t), &wifiSendQueue_attributes);

    wifiRecvTaskHandle = osThreadNew(wifiRecvTask, NULL, &wifiRecvTask_attributes);
    wifiSendTaskHandle = osThreadNew(wifiSendTask, NULL, &wifiSendTask_attributes);
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
            //printf("接收到消息\n");
            wifi_recv_msg_handle(&msg); // 解析并处理接收到的 WiFi 消息
        }
    }
}

/* WiFi 发送任务 --------------------------------------------------------- */
void wifiSendTask(void *argument)
{

    // 初始化 WiFi 模块，配置 SSID 和密码
    wifi_init("zhongxu", "18568601031");
    wifi_connect();
    mqtt_init("esp8266-yunsg13", "zhongxu", "310514", "82.156.68.10", "1883", "60");
    WifiCommand_t cmd = {0};

    while (1)
    {
        // 阻塞等待发送队列中的命令
        if (osMessageQueueGet(wifiSendQueueHandle, &cmd, NULL, osWaitForever) == osOK)
        {
            //printf("发送命令\n");
            wifi_send_message_handle(&cmd); // 处理并发送命令到 WiFi 模块
        }
    }
}
