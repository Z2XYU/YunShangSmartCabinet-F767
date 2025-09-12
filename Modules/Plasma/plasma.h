#pragma once

#include "main.h"

typedef struct
{
    GPIO_TypeDef* port;
    uint16_t pin;
} Plasma_t;

extern Plasma_t plasmas[2];

void plasma_on(Plasma_t *device);
void plasma_off(Plasma_t *device);

void plasma_on_all(void);
void plasma_off_all(void);