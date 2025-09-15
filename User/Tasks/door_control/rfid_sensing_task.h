#pragma once

#include "main.h"
#include "cmsis_os2.h"

extern osThreadId_t rfidSensingTaskHandle;
extern osSemaphoreId_t recogDoneSemaphoreHandle;
extern osMessageQueueId_t rfidQueueHandle;

void rfidSensingTask(void *argument);
void rfid_task_init(void);