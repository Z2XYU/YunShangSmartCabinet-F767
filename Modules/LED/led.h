#pragma once

#include "main.h"

typedef struct {
    GPIO_TypeDef* port;
    uint16_t pin;
} LED_TypeDef;

#define LED0    ((LED_TypeDef){GPIOB,GPIO_PIN_1})
#define LED1    ((LED_TypeDef){GPIOB,GPIO_PIN_0})

void led_on(const LED_TypeDef *led);
void led_off(const LED_TypeDef *led);
void led_toggle(const LED_TypeDef *led);