#include "a4988.h"

void a4988_set_dir(GPIO_TypeDef *port, uint16_t pin, uint8_t dir)
{
    HAL_GPIO_WritePin(port, pin, dir ? GPIO_PIN_SET : GPIO_PIN_RESET);
}

void a4988_enable(GPIO_TypeDef *port, uint16_t pin)
{
    HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);
}

void a4988_disenable(GPIO_TypeDef *port, uint16_t pin)
{
    HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET);
}

void a4988_step(GPIO_TypeDef *port, uint16_t pin)
{
    HAL_GPIO_WritePin(port, pin, GPIO_PIN_SET);
    for (volatile int i = 0; i < 50; i++);
    HAL_GPIO_WritePin(port, pin, GPIO_PIN_RESET);
}