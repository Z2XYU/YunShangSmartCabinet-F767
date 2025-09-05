#pragma once

#include "main.h"
#include "cmsis_os2.h"

extern osMutexId_t wifiStateMutex;
extern osMessageQueueId_t wifiSendQueueHandle;
extern osMessageQueueId_t wifiRecvQueueHandle;
extern osThreadId_t wifiRecvTaskHandle;
extern osThreadId_t wifiSendTaskHandle;

void wifi_communication_task_init(void);
void wifiRecvTask(void *argument);
void wifiSendTask(void *argument);