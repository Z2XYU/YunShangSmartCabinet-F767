#pragma once

#include "main.h"
#include "cmsis_os2.h"
#include "sh40.h"

extern SH40_t sh40_sensor;
extern osMutexId_t sh40MeasMutexHandle;
extern osThreadId_t envMeasTaskHandle;;

void env_meas_tasks_init(void);

void envMeasTask(void *argument);