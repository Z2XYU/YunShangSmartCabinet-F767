#include "sh40.h"
#include "soft_iic.h"
#include "crc.h"
#include "dwt.h"

#define SH40_ADDRESS 0x44
#define SH40_MEASURE_CMD 0xFD
/*读取唯一序列号*/
#define SH40_SERIAL_NUMBER 0x89

#define SH40_WRITE (0x44 << 1)
#define SH40_READ ((0x44 << 1) | 1)

#define SHT40_CRC8_POLY 0x31 // x^8 + x^5 + x^4 + 1
#define SHT40_CRC8_INIT 0xFF // 初始值



SH40_t sh40_measurement_data(void)
{
    SH40_t sensor={0};
    iic_start();
    iic_send_byte(SH40_WRITE);
    iic_wait_ack();
    iic_send_byte(SH40_MEASURE_CMD);
    iic_wait_ack();
    iic_stop();

    dwt_delay_ms(9);

    iic_start();
    iic_send_byte(SH40_READ);
    iic_wait_ack();

    uint8_t temperature_h = iic_read_byte(1);
    uint8_t temperature_l = iic_read_byte(1);
    uint8_t temperature_crc = iic_read_byte(1);

    uint8_t humidity_h = iic_read_byte(1);
    uint8_t humidity_l = iic_read_byte(1);

    uint8_t humidity_crc = iic_read_byte(0);

    iic_stop();

    /*校验*/
    uint8_t temp_raw[2] = {temperature_h, temperature_l};
    uint8_t humi_raw[2] = {humidity_h, humidity_l};

    if (crc8_calculation(temp_raw, 2, SHT40_CRC8_INIT, SHT40_CRC8_POLY) != temperature_crc)
    {
        sensor.temperature = SH40_INVALID_VALUE;
    }
    else
    {
        uint16_t temp = ((uint16_t)temperature_h << 8) | temperature_l;
        sensor.temperature = -45.0f + 175.0f * (float)temp / 65535.0f;
    }

    if (crc8_calculation(humi_raw, 2, SHT40_CRC8_INIT, SHT40_CRC8_POLY) != humidity_crc)
    {
        sensor.humidity = SH40_INVALID_VALUE;
    }
    else
    {
        uint16_t hum = ((uint16_t)humidity_h << 8) | humidity_l;
        sensor.humidity = -6.0f + 125.0f * (float)hum / 65535.0f;
    }
    return sensor;
}

uint32_t sh40_read_serial_number(void)
{
    uint32_t serial_number;

    uint32_t data[4];
    iic_start();

    iic_send_byte(SH40_WRITE);      // 发送写地址
    iic_wait_ack();
    iic_send_byte(SH40_SERIAL_NUMBER); // 发送读取序列号命令
    iic_wait_ack();

    dwt_delay_ms(10);               // 等待数据准备

    iic_start();
    iic_send_byte(SH40_READ);       // 发送读地址
    iic_wait_ack();

    data[0] = iic_read_byte(1);     // 读取序列号高字节
    data[1] = iic_read_byte(1);     // 读取序列号次高字节
    data[2] = iic_read_byte(1);     // 读取序列号次低字节
    data[3] = iic_read_byte(0);     // 读取序列号低字节（最后一字节不应发送 ACK）

    iic_stop();

    // 合成32位序列号
    serial_number = ((data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3]);
    return serial_number;
}
