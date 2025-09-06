#pragma once

#include "main.h"

void a4988_enable(GPIO_TypeDef *port, uint16_t pin);
void a4988_set_dir(GPIO_TypeDef *port, uint16_t pin, uint8_t dir);
void a4988_disenable(GPIO_TypeDef *port, uint16_t pin);
void a4988_step(GPIO_TypeDef *port, uint16_t pin);