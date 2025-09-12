#include "plasma.h"

#define PLASMA_NUM 2

Plasma_t plasmas[] = {
    {plasmas1_GPIO_Port, plasmas1_Pin},
    {plasmas2_GPIO_Port, plasmas2_Pin}};

void plasma_on(Plasma_t *device)
{
    HAL_GPIO_WritePin(device->port,device->pin,GPIO_PIN_RESET);
}

void plasma_off(Plasma_t *device)
{
    HAL_GPIO_WritePin(device->port,device->pin,GPIO_PIN_SET);
}

void plasma_on_all(void)
{
    for(uint8_t i=0;i<PLASMA_NUM;i++)
    {
        plasma_on(&plasmas[i]);
    }
}

void plasma_off_all(void)
{
    for(uint8_t i=0;i<PLASMA_NUM;i++)
    {
        plasma_off(&plasmas[i]);
    }
}