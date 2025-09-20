#include "tc_tasks.h"
#include "pca9685.h"
#include "pid.h"
#include "ptc.h"
#include "tec.h"
#include "fan.h"
#include "env_meas_tasks.h"

osThreadId_t temperatureControlTaskHandle;
const osThreadAttr_t temperatureControlTask_attributes = {
    .name = "temperatureControlTask",
    .stack_size = 128 * 8,
    .priority = (osPriority_t)osPriorityNormal4};

PID_TypeDef pid = {
    .Kp = 3.0f,
    .Ki = 0.4f,
    .Kd = 0.8f,
    .set_point = 25.0f,
    .prev_error = 0.0f,
    .integral = 0.0f,
    .output = 0.0f,
    .dt = 1.0f,
    .out_min = -100.0f,
    .out_max = 100.0f};

void tc_tasks_init(void)
{
    pca9685_init(500);
    ptc_init();
    tec_init();
    temperatureControlTaskHandle = osThreadNew(temperatureControlTask, NULL, &temperatureControlTask_attributes);
}

static void temperature_control(float pid_out)
{
    const float DEAD_ZONE = 0.3f;
    if (pid_out > DEAD_ZONE)
    {
        ptc_set_power(pid_out);
        tec_set_power(0);
    }
    else if (pid_out < -DEAD_ZONE)
    {
        ptc_set_power(0);
        tec_set_power(pid_out);
    }
    else
    {
        ptc_set_power(0);
        tec_set_power(0);
    }
}

void temperatureControlTask(void *argument)
{
    while (1)
    {
        float output = pid_computer(&pid, sht40_sensor.temperature);
        temperature_control(output);
        osDelay(1000); // 每2000ms执行一次
    }
}