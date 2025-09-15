#include "crc.h"

uint8_t crc8_calculation(uint8_t *data, int len, uint8_t init, uint8_t poly)
{
    uint8_t crc = init;

    for (int i = 0; i < len; i++)
    {
        crc ^= data[i];
        for (int j = 0; j < 8; j++)
        {
            if (crc & 0x80)
            {
                crc = (crc << 1) ^ poly;
            }
            else
            {
                crc <<= 1;
            }
        }
    }
    return crc;
}