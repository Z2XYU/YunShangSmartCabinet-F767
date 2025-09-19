#pragma once

#include "main.h"

#define PCA9685_ADDRESS 0x40
#define PCA9685_WRITE_ADDRESS (0x40 << 1)
#define PCA9685_READ_ADDRESS ((0x40 << 1) | 1)

#define MODE1_REG 0x00
#define MODE2_REG 0x01
#define PRESCALE_REG 0xFE
#define CHANNEL_BASE_ADDR   0x06

#define MODE1_RESTART   0x80
#define MODE1_SLEEP     0x10
#define MODE1_AUTOINC   0x20
#define MODE1_ALLCALL   0x01

#define PTC1_CHANNEL 0
#define PTC2_CHANNEL 1
#define TEC1_CHANNEL 2
#define TEC2_CHANNEL 3
#define FAN_CHANNEL 4


void pca9685_init(uint16_t freq);
void pca9685_write_reg(uint8_t reg, uint8_t data);
uint8_t pca9685_read_reg(uint8_t reg);
void pca9685_set_frequency(uint16_t freq);
void pca9685_set_pwm(uint8_t channel, uint16_t on, uint16_t off);
void pca9685_set_duty(uint8_t channel, float duty);