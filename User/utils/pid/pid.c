#include "pid.h"
#include <math.h>

float pid_computer(PID_TypeDef *pid, float current)
{
    if (pid == NULL || pid->dt <= 0.0f)
    {
        return 0.0f;
    }
    float error = pid->set_point - current;

    /*积分分离*/
    if (fabs(error) < 10.0f)
    {
        pid->integral += error * pid->dt;
    }

    /*积分限幅*/
    const float integral_limit = 100.0f;
    if (pid->integral > integral_limit)
        pid->integral = integral_limit;
    if (pid->integral < -integral_limit)
        pid->integral = -integral_limit;

    /*微分计算*/
    float derivative = (error - pid->prev_error) / pid->dt;

    /*PID计算*/
    float output = pid->Kp * error + pid->Ki * pid->integral + pid->Kd * derivative;

    /*输出限幅*/
    if (output > pid->out_max)
        output = pid->out_max;
    if (output < pid->out_min)
        output = pid->out_min;

    /*状态更新*/
    pid->prev_error = error;
    pid->output = output;

    return output;
}