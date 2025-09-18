#pragma once

#include "main.h"
#include "cmsis_os2.h"


extern osThreadId_t temperatureControlTaskHandle;

void tc_tasks_init(void);
void temperatureControlTask(void *argument);