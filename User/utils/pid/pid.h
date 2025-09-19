#pragma once

#include "main.h"

typedef struct 
{
    float Kp;
    float Ki;
    float Kd;

    float set_point;
    float prev_error;
    float integral;
    float output;
    float dt;
    float out_min;
    float out_max;
}PID_TypeDef;

float pid_computer(PID_TypeDef *pid, float current);
