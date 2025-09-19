#pragma once

#include "main.h"

#define SH40_INVALID_VALUE (-999.0f)

typedef struct
{
    float temperature;
    float humidity;
} SHT40_t;

SHT40_t sht40_measurement_data(void);
uint32_t sht40_read_serial_number(void);