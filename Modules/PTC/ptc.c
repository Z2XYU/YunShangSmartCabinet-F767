#include "ptc.h"
#include "pca9685.h"

void ptc_init(void)
{
    pca9685_set_duty(PTC1_CHANNEL, 0);
    pca9685_set_duty(PTC2_CHANNEL, 0);
}

void ptc_set_power(float power)
{
    if (power > 100)
        power = 100;
    else if (power < 0)
        power = 0;
    pca9685_set_duty(PTC1_CHANNEL, power);
    pca9685_set_duty(PTC2_CHANNEL, power);
}