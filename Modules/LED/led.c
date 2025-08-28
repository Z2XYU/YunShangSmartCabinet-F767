#include "led.h"


void led_on(const LED_TypeDef *led)
{
    HAL_GPIO_WritePin(led->port,led->pin,GPIO_PIN_RESET);
}

void led_off(const LED_TypeDef *led)
{
    HAL_GPIO_WritePin(led->port,led->pin,GPIO_PIN_SET);
}

void led_toggle(const LED_TypeDef *led)
{
    HAL_GPIO_TogglePin(led->port,led->pin);
}