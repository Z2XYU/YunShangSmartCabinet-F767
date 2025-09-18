// pca9685.c
#include "pca9685.h"
#include "soft_iic.h"
#include "dwt.h"   

#define LED0_BASE 0x06

// 写寄存器
void pca9685_write_reg(uint8_t reg, uint8_t data)
{
    iic_start();
    iic_send_byte(PCA9685_ADDRESS << 1); // 7位地址左移1位作为写地址
    iic_wait_ack();
    iic_send_byte(reg);
    iic_wait_ack();
    iic_send_byte(data);
    iic_wait_ack();
    iic_stop();
}

// 读寄存器
uint8_t pca9685_read_reg(uint8_t reg)
{
    iic_start();
    iic_send_byte(PCA9685_ADDRESS << 1); // 写模式
    iic_wait_ack();
    iic_send_byte(reg);
    iic_wait_ack();

    iic_start();
    iic_send_byte((PCA9685_ADDRESS << 1) | 0x01); // 读模式
    uint8_t data = iic_read_byte(0);
    iic_stop();
    return data;
}

// 设置 PWM 频率
void pca9685_set_frequency(uint16_t freq)
{
    uint8_t prescale;

    // 计算分频器值
    prescale = (uint8_t)(25000000 / (4096 * freq) - 1);

    // 进入睡眠模式，设置频率
    pca9685_write_reg(MODE1_REG, 0x80);  // 进入睡眠模式
    HAL_Delay(10);                   // 等待 10ms

    pca9685_write_reg(PRESCALE_REG, prescale);   // 设置分频器
    HAL_Delay(10);                   // 等待 10ms

    pca9685_write_reg(MODE1_REG, 0xA1);  // 退出睡眠模式
    HAL_Delay(10);                   // 等待 10ms
}

// 设置单通道 PWM
void pca9685_set_pwm(uint8_t channel, uint16_t on, uint16_t off)
{
    if(channel > 15) return;

    uint8_t base = LED0_BASE + 4 * channel;

    iic_start();
    iic_send_byte(PCA9685_ADDRESS << 1);
    iic_wait_ack();
    iic_send_byte(base);
    iic_wait_ack();

    iic_send_byte(on & 0xFF);
    iic_wait_ack();
    iic_send_byte((on >> 8) & 0x0F);
    iic_wait_ack();
    iic_send_byte(off & 0xFF);
    iic_wait_ack();
    iic_send_byte((off >> 8) & 0x0F);
    iic_wait_ack();

    iic_stop();
}

// 设置占空比 0~100%
void pca9685_set_duty(uint8_t channel, float duty)
{
    if(duty <= 0.0f)
        pca9685_set_pwm(channel, 0, 4096); // 全关
    else if(duty >= 100.0f)
        pca9685_set_pwm(channel, 0, 0);    // 全开
    else
    {
        uint16_t off = (uint16_t)(4096.0f * duty / 100.0f);
        pca9685_set_pwm(channel, 0, off);
    }
}

// 初始化 PCA9685
void pca9685_init(uint16_t freq)
{

    // 设置 PWM 频率
    pca9685_set_frequency(freq);

    // 初始化16通道 PWM 占空比为0（全关）
    for(uint8_t i = 0; i < 16; i++)
        pca9685_set_pwm(i, 0, 4096);
}
