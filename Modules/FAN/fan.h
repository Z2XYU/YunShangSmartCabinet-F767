#pragma once

#include "main.h"
#include "pca9685.h"


void fan_on(void);
void fan_off(void);
void fan_set_power(uint8_t power);