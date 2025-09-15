#pragma once

#include "main.h"

#define SH40_INVALID_VALUE (-999.0f)

typedef struct
{
    float temperature;
    float humidity;
} SH40_t;

SH40_t sh40_measurement_data(void);
uint32_t sh40_read_serial_number(void);