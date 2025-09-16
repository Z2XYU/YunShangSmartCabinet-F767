#pragma once

#include "main.h"
#include "rtc.h"

typedef struct
{
    RTC_TimeTypeDef sTime;
    RTC_DateTypeDef sDate;
} Clock_t;

void clock_get_time(void);
void rtc_set_alarm_30min(void);
void clock_set_time(Clock_t *clk);