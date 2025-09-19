#include "fan.h"

void fan_set_power(uint8_t power)
{
    pca9685_set_duty(FAN_CHANNEL,power);
}

void fan_on(void)
{
    pca9685_set_duty(FAN_CHANNEL,100);
}

void fan_off(void)
{
    pca9685_set_duty(FAN_CHANNEL,0);
}
