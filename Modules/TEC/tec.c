#include "tec.h"
#include "pca9685.h"

void tec_init(void)
{
    pca9685_set_duty(TEC1_CHANNEL,0);
    pca9685_set_duty(TEC2_CHANNEL,0);
}

void tec_set_power(float power)
{
    pca9685_set_duty(TEC1_CHANNEL,power);
    pca9685_set_duty(TEC2_CHANNEL,power);
}