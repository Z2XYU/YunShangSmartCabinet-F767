#pragma once

#include "main.h"
#include "cmsis_os2.h"

extern osThreadId_t lvglRefreshTaskHandle;

void ui_refresh_tasks_init(void);
void lvglRefreshTask(void *argument);