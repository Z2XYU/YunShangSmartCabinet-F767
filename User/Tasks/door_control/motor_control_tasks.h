#pragma once

#include "main.h"
#include "cmsis_os2.h"
#include "door_types.h"

#define MOTOR_NUM 2

typedef struct
{
    int clothes_id;
    char action[16];
    char option[16];
    int cabinet_location;
} MotorControl_t;


extern StepperMotor_t motors[MOTOR_NUM];
extern DoorController_t doors[MOTOR_NUM];
extern osThreadId_t motorCalibrationTaskHandle;
extern osThreadId_t motorControlTaskHandle;
extern osMessageQueueId_t motorControlMsgQueueHandle;

void motorCalibrationTask(void *argument);
void motorCommTask(void *argument);
void motor_control_tasks_init(void);
