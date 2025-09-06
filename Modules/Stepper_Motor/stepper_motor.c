#include "stepper_motor.h"
#include "a4988.h"
#include <math.h>

void stepper_motor_init(StepperMotor_t *motor,
                        GPIO_TypeDef *dir_port, uint16_t dir_pin,
                        GPIO_TypeDef *step_port, uint16_t step_pin,
                        GPIO_TypeDef *en_port, uint16_t en_pin,
                        TIM_HandleTypeDef *htim)
{
    motor->dir_port = dir_port;
    motor->dir_pin = dir_pin;
    motor->step_port = step_port;
    motor->step_pin = step_pin;
    motor->en_port = en_port;
    motor->en_pin = en_pin;
    motor->htim = htim;

    motor->target_steps = 0;
    motor->current_steps = 0;
    motor->max_speed_hz = 0;
    motor->min_speed_hz = 100;
    motor->accel = 0;
    motor->decel = 0;
    motor->current_speed = 0;
    motor->step_interval_us = 0;
    motor->busy = 0;
    motor->accel_steps = 0;
    motor->decel_steps = 0;

    stepper_motor_disable(motor);
    stepper_motor_set_direction(motor, 0);
}

void stepper_motor_enable(StepperMotor_t *motor)
{
    a4988_enable(motor->en_port, motor->en_pin);
}

void stepper_motor_disable(StepperMotor_t *motor)
{
    a4988_disenable(motor->en_port, motor->en_pin);
}

void stepper_motor_set_direction(StepperMotor_t *motor, uint8_t dir)
{
    a4988_set_dir(motor->dir_port, motor->dir_pin, dir);
}

void stepper_motor_move_steps(StepperMotor_t *motor, int32_t steps,
                              uint32_t vmax, uint32_t accel, uint32_t decel)
{
    if (steps == 0) return;

    motor->target_steps = (steps > 0) ? steps : -steps;
    motor->current_steps = 0;

    motor->max_speed_hz = vmax;
    motor->min_speed_hz = 500;
    motor->accel = accel;
    motor->decel = decel;

    motor->current_speed = motor->min_speed_hz;

    motor->accel_steps = (uint32_t)((float)vmax * vmax / (2.0f * accel));
    motor->decel_steps = (uint32_t)((float)vmax * vmax / (2.0f * decel));

    if (motor->accel_steps + motor->decel_steps > motor->target_steps)
    {
        float vmax_tri = sqrtf(2.0f * motor->target_steps * accel * decel / (accel + decel));
        motor->accel_steps = (uint32_t)(vmax_tri * vmax_tri / (2.0f * accel));
        motor->decel_steps = motor->target_steps - motor->accel_steps;
        motor->max_speed_hz = (uint32_t)vmax_tri;
    }

    stepper_motor_set_direction(motor, (steps > 0));

    motor->step_interval_us = 1000000.0f / motor->current_speed;
    __HAL_TIM_SET_AUTORELOAD(motor->htim, (uint32_t)motor->step_interval_us);

    motor->busy = 1;
    HAL_TIM_Base_Start_IT(motor->htim);
}

uint8_t stepper_motor_is_busy(StepperMotor_t *motor)
{
    return motor->busy;
}

void stepper_motor_on_timer_interrupt(StepperMotor_t *motor)
{
    if (!motor->busy) return;

    a4988_step(motor->step_port, motor->step_pin);
    motor->current_steps++;

    if (motor->current_steps >= motor->target_steps)
    {
        motor->busy = 0;
        HAL_TIM_Base_Stop_IT(motor->htim);
        return;
    }

    if (motor->current_steps < motor->accel_steps)
    {
        motor->current_speed += (float)motor->accel / 1000.0f;
        if (motor->current_speed > motor->max_speed_hz)
            motor->current_speed = motor->max_speed_hz;
    }
    else if (motor->target_steps - motor->current_steps <= motor->decel_steps)
    {
        motor->current_speed -= (float)motor->decel / 1000.0f;
        if (motor->current_speed < motor->min_speed_hz)
            motor->current_speed = motor->min_speed_hz;
    }
    else
    {
        motor->current_speed = motor->max_speed_hz;
    }

    motor->step_interval_us = 1000000.0f / motor->current_speed;
    if (motor->step_interval_us < 200)
        motor->step_interval_us = 200;

    __HAL_TIM_SET_AUTORELOAD(motor->htim, (uint32_t)motor->step_interval_us);
}
