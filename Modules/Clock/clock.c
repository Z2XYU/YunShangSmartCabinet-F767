#include "clock.h"
#include "rtc.h"
#include "plasma.h"

void HAL_RTC_AlarmAEventCallback(RTC_HandleTypeDef *hrtc)
{
    plasma_off(&plasmas[0]);
}

void rtc_set_alarm_30min(void)
{
    RTC_TimeTypeDef current_time={0};
    RTC_AlarmTypeDef alarm = {0};

    HAL_RTC_GetTime(&hrtc,&current_time,RTC_FORMAT_BIN);
    
    alarm.AlarmTime.Hours = current_time.Hours;
    alarm.AlarmTime.Minutes = current_time.Minutes + 30;
    alarm.AlarmTime.Seconds = 0;

    if(alarm.AlarmTime.Minutes>=60)
    {
        alarm.AlarmTime.Hours+=1;
        alarm.AlarmTime.Minutes-=60;
        if(alarm.AlarmTime.Hours >= 24)
            alarm.AlarmTime.Hours -= 24;
    }

    alarm.AlarmMask = RTC_ALARMMASK_NONE;
    alarm.AlarmSubSecondMask = RTC_ALARMSUBSECONDMASK_ALL;
    alarm.AlarmDateWeekDaySel = RTC_ALARMDATEWEEKDAYSEL_DATE;
    alarm.AlarmDateWeekDay = 1;
    alarm.Alarm = RTC_ALARM_A;

    HAL_RTC_SetAlarm_IT(&hrtc,&alarm,RTC_FORMAT_BIN);
}

/*保留 通过 wifi 获取网络时间*/
//https://sapi.k780.com/?app=life.time&appkey=10003&sign=b59bc3ef6191eb9f747dd4e83c99f2a4&format=json 北京时间api
void clock_init(void)
{

}