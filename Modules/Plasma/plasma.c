#include "plasma.h"

void plasma_on(Plasma_t *device)
{
    HAL_GPIO_WritePin(device->port,device->pin,GPIO_PIN_RESET);
}

void plasma_off(Plasma_t *device)
{
    HAL_GPIO_WritePin(device->port,device->pin,GPIO_PIN_SET);
}