#include "door_contact.h"

GPIO_PinState read_door_sta(GPIO_TypeDef *port,uint16_t pin)
{
    return HAL_GPIO_ReadPin(port,pin);
}