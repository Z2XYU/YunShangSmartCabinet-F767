#include "env_meas_tasks.h"
#include "sh40.h"
#include "stdio.h"
#include "gui_guider.h"
#include "custom.h"

osThreadId_t envMeasTaskHandle;
const osThreadAttr_t envMeasTas_attributes = {
    .name = "envMeasTask",
    .stack_size = 128 * 8,
    .priority = (osPriority_t)osPriorityNormal};

osMutexId_t sh40MeasMutexHandle;
const osMutexAttr_t sh40MeasMutex_attributes = {
    .name = "sh40MeasMutex"};

SH40_t sh40_sensor = {0};

void env_meas_tasks_init(void)
{
    sh40MeasMutexHandle = osMutexNew(&sh40MeasMutex_attributes);
    if (sh40MeasMutexHandle == NULL)
    {
        printf("Failed to create SH40 mutex!\r\n");
    }
    envMeasTaskHandle = osThreadNew(envMeasTask, NULL, &envMeasTas_attributes);
}

void envMeasTask(void *argument)
{
    while (1)
    {
        SH40_t sensor = sh40_measurement_data();

        if (sensor.humidity == SH40_INVALID_VALUE || sensor.temperature == SH40_INVALID_VALUE)
        {
            printf("SH40 measurement failed\r\n");
        }
        else
        {
            if (osMutexAcquire(sh40MeasMutexHandle, 100) == osOK)
            {
                sh40_sensor = sensor;
                osMutexRelease(sh40MeasMutexHandle);
                printf("humi: %.2f temp:%.2f\n", sh40_sensor.humidity, sh40_sensor.temperature);
            }
            else
            {
                printf("Failed to acquire SH40 mutex!\r\n");
            }
        }
        osDelay(1000);
    }
}