#pragma once

#ifdef __cplusplus
extern "C"
{
#endif
#include "main.h"
#include "cmsis_os2.h"
#include "stepper_motor.h"

typedef struct
{
    int clothes_id;
    char action[16];
    char option[16];
    int cabinet_location;
} MotorControl_t;

extern StepperMotor_t motors[2];

void motorControlTask(void *argument);
void motor_control_tasks_init(void);

#ifdef __cplusplus
}
#endif