#include "tc_tasks.h"
#include "pca9685.h"

osThreadId_t temperatureControlTaskHandle;
const osThreadAttr_t temperatureControlTask_attributes = {
    .name = "temperatureControlTask",
    .stack_size = 128 * 8,
    .priority = (osPriority_t)osPriorityNormal};

void tc_tasks_init(void)
{
    temperatureControlTaskHandle = osThreadNew(temperatureControlTask,NULL,&temperatureControlTask_attributes);
}

void temperatureControlTask(void *argument)
{
    pca9685_init(500);
    pca9685_set_duty(0,70);
    pca9685_set_duty(1,20);

    while (1)
    {
        osDelay(50);
    }
}