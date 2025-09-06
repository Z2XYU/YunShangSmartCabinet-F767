#ifndef __STEPPER_MOTOR_H
#define __STEPPER_MOTOR_H

#include "main.h"

#ifdef __cplusplus
extern "C" {
#endif

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

/* ====== API 接口 ====== */
void stepper_motor_init(StepperMotor_t *motor,
                        GPIO_TypeDef *dir_port, uint16_t dir_pin,
                        GPIO_TypeDef *step_port, uint16_t step_pin,
                        GPIO_TypeDef *en_port, uint16_t en_pin,
                        TIM_HandleTypeDef *htim);

void stepper_motor_enable(StepperMotor_t *motor);
void stepper_motor_disable(StepperMotor_t *motor);
void stepper_motor_set_direction(StepperMotor_t *motor, uint8_t dir);

void stepper_motor_move_steps(StepperMotor_t *motor, int32_t steps,
                              uint32_t vmax, uint32_t accel, uint32_t decel);

uint8_t stepper_motor_is_busy(StepperMotor_t *motor);

void stepper_motor_on_timer_interrupt(StepperMotor_t *motor);

#ifdef __cplusplus
}
#endif

#endif /* __STEPPER_MOTOR_H */
