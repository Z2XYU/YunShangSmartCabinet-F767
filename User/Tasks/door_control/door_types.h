#pragma once

#include "main.h"

typedef struct
{
    GPIO_TypeDef *dir_port;
    uint16_t dir_pin;

    GPIO_TypeDef *step_port;
    uint16_t step_pin;

    GPIO_TypeDef *en_port;
    uint16_t en_pin;

    TIM_HandleTypeDef *htim;

    int32_t target_steps;
    int32_t current_steps;

    uint32_t max_speed_hz; // 最大速度
    uint32_t min_speed_hz; // 最小启动速度
    uint32_t accel;        // 加速度 (Hz/s)
    uint32_t decel;        // 减速度 (Hz/s)

    float current_speed;    // 当前速度 (Hz)
    float step_interval_us; // 当前脉冲间隔 (us)

    uint8_t busy;

    // 梯形速度规划辅助变量
    uint32_t accel_steps;
    uint32_t decel_steps;
} StepperMotor_t;


typedef enum
{
    DOOR_IDLE = 0,
    DOOR_OPENING,
    DOOR_CLOSEING,

} DoorState_e;

typedef struct
{
    GPIO_TypeDef *sensor_port;
    uint16_t sensor_pin;
} MagneticSensor_t;

typedef struct
{
    StepperMotor_t *motor;
    DoorState_e state;
    MagneticSensor_t *sensor;
    uint8_t sensor_flag;
    int32_t target_steps;
} DoorController_t;