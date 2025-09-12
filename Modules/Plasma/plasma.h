#pragma once

#include "main.h"

typedef struct
{
    GPIO_TypeDef* port;
    uint16_t pin;
} Plasma_t;

void plasma_on(Plasma_t *device);
void plasma_off(Plasma_t *device);