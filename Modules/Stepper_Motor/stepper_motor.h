#pragma once

#include "main.h"
#include "motor_control_tasks.h"
#include "door_types.h"

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


void door_open(StepperMotor_t *motor);
void door_close(StepperMotor_t *motor);
void door_calibration(DoorController_t *door);

