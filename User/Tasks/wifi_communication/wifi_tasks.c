#include "wifi_tasks.h"
#include "wifi_comm.h"
#include "esp8266.h"
#include <stdio.h>

/*Tasks----------------------------------------*/
/*wifi接收任务*/
osMessageQueueId_t wifiRecvQueueHandle;
const osMessageQueueAttr_t wifiRecvQueue_attributes = {
    .name = "wifiRecvQueue",
};
osMessageQueueId_t wifiSendQueueHandle;
const osMessageQueueAttr_t wifiSendQueue_attributes = {
    .name = "wifiSendQueue",
};

osMutexId_t wifiStateMutex;

osThreadId_t wifiRecvTaskHandle;
const osThreadAttr_t wifiRecvTask_attributes = {
    .name = "wifiRecvTask",
    .stack_size = 128 * 8,
    .priority = (osPriority_t)osPriorityHigh,
};
osThreadId_t wifiSendTaskHandle;
const osThreadAttr_t wifiSendTask_attributes = {
    .name = "wifiSendTask",
    .stack_size = 128 * 8,
    .priority = (osPriority_t)osPriorityHigh,
};
osThreadId_t wifiMonitorTaskHandle;
const osThreadAttr_t wifiMonitorTask_attributes = {
    .name = "wifiMonitorTask",
    .stack_size = 128 * 4,
    .priority = (osPriority_t)osPriorityNormal,
};

void wifi_communication_task_init(void)
{
    wifiStateMutex = osMutexNew(NULL);
    wifiRecvQueueHandle = osMessageQueueNew(10, sizeof(WifiMessage_t), &wifiSendQueue_attributes);
    wifiSendQueueHandle = osMessageQueueNew(10, sizeof(WifiCommand_t), &wifiSendQueue_attributes);
    wifiMonitorTaskHandle = osThreadNew(wifiMonitorTask, NULL, &wifiMonitorTask_attributes);
    wifiRecvTaskHandle = osThreadNew(wifiRecvTask, NULL, &wifiRecvTask_attributes);
    wifiSendTaskHandle = osThreadNew(wifiSendTask, NULL, &wifiSendTask_attributes);
}

void wifiMonitorTask(void *argument)
{
    wifi_init("zhongxu", "18568601031");

    WifiState_t wifi_state = {0};

    while (1)
    {
        wifi_state = wifi_get_status();

        switch (wifi_state.status)
        {
        case WL_CONNECTED:
            printf("WiFi 已连接: %s\n", wifi_state.ssid);
            wifi_status_update(); // 发送状态
            osDelay(10000);       // 10 秒轮询
            break;

        case WL_DISCONNECTED:
        case WL_CONNECT_FAILED:
        case WL_WRONG_PASSWORD:
            printf("WiFi 未连接，尝试重连...\n");
            wifi_connect();       // 触发连接
            osDelay(5000);
            wifi_status_update();
            break;

        case WL_IDLE_STATUS:
        case WL_SCAN_COMPLETED:
        case WL_NO_SSID_AVAIL:
        case WL_CONNECTION_LOST:
        case WL_NO_SHIELD:
        default:
            osDelay(2000);
            break;
        }
    }
}



void wifiRecvTask(void *argument)
{
    WifiMessage_t msg = {0};
    while (1)
    {
        if (osMessageQueueGet(wifiRecvQueueHandle, &msg, NULL, osWaitForever) == osOK)
        {
            wifi_recv_msg_handle(&msg);
        }
    }
}

void wifiSendTask(void *argument)
{
    WifiCommand_t msg = {0};
    while (1)
    {
        if (osMessageQueueGet(wifiSendQueueHandle, &msg, NULL, osWaitForever) == osOK)
        {
            wifi_send_message_handle(&msg);
            printf("发送命令\n");
        }
    }
}