#include "clock.h"
#include "rtc.h"
#include "plasma.h"
#include "gui_guider.h"
#include "cJSON.h"
#include "wifi_comm.h"

void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc)
{
    plasma_off(&plasmas[0]);
}

void rtc_set_alarm_30min(void)
{
    RTC_TimeTypeDef current_time = {0};
    RTC_AlarmTypeDef alarm = {0};

    HAL_RTC_GetTime(&hrtc, &current_time, RTC_FORMAT_BIN);

    alarm.AlarmTime.Hours = current_time.Hours;
    alarm.AlarmTime.Minutes = current_time.Minutes + 30;
    alarm.AlarmTime.Seconds = 0;

    if (alarm.AlarmTime.Minutes >= 60)
    {
        alarm.AlarmTime.Hours += 1;
        alarm.AlarmTime.Minutes -= 60;
        if (alarm.AlarmTime.Hours >= 24)
            alarm.AlarmTime.Hours -= 24;
    }

    alarm.AlarmMask = RTC_ALARMMASK_NONE;
    alarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_ALL;
    alarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
    alarm.AlarmDateWeekDay = 1;
    alarm.Alarm = RTC_ALARM_A;

    HAL_RTC_SetAlarm_IT(&hrtc, &alarm, RTC_FORMAT_BIN);
}

void clock_get_time(void)
{
    WifiCommand_t msg = {0};

    strncpy(msg.type, "http", sizeof(msg.type) - 1);
    strncpy(msg.cmd, "get_time", sizeof(msg.cmd) - 1);

    wifi_send_msg_to_queue(&msg, 0);
}

extern int screen_1_digital_clock_1_hour_value;
extern int screen_1_digital_clock_1_min_value;
extern int screen_1_digital_clock_1_sec_value;
extern char screen_1_date_text[16];

/*保留 通过 wifi 获取网络时间*/
void clock_set_time(Clock_t *clk)
{
    HAL_RTC_SetDate(&hrtc, &clk->sDate, RTC_FORMAT_BIN);
    HAL_RTC_SetTime(&hrtc, &clk->sTime, RTC_FORMAT_BIN);
    screen_1_digital_clock_1_hour_value = clk->sTime.Hours;
    screen_1_digital_clock_1_min_value = clk->sTime.Minutes;
    screen_1_digital_clock_1_sec_value = clk->sTime.Seconds;

    sprintf(screen_1_date_text, "%04d/%02d/%02d",clk->sDate.Year+2000,clk->sDate.Month,clk->sDate.Date);
}