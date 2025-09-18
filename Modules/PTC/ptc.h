#pragma once

#include "main.h"

#define PTC1_CHANNEL 0
#define PTC2_CHANNEL 1

void ptc_init(void);
void ptc_set_power(float power);