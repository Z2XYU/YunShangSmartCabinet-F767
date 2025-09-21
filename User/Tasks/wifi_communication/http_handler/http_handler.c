#include "http_handler.h"
#include "ui_tasks.h"
#include <stdio.h>

void get_beijing_time_pack(WifiCommand_t *msg, cJSON *root)
{
    cJSON *data = cJSON_CreateObject();
    cJSON_AddItemToObject(root, "data", data);
}

static void set_beijing_time(WifiMessage_t *msg, cJSON *data)
{
    if (!msg || !data)
        return;
    // printf("处理时间\n");
    if (cJSON_IsString(data))
    {
        int year, month, day, hour, min, sec;
        sscanf(data->valuestring, "%d-%d-%d %d:%d:%d",
               &year, &month, &day, &hour, &min, &sec);

        msg->data.clock.sDate.Year = year - 2000;
        msg->data.clock.sDate.Month = month;
        msg->data.clock.sDate.Date = day;
        msg->data.clock.sTime.Hours = hour;
        msg->data.clock.sTime.Minutes = min;
        msg->data.clock.sTime.Seconds = sec;
    }
}
void http_msg_parse(WifiMessage_t *msg, const char *json_str)
{
    if (!msg || !json_str)
        return;

    cJSON *root = cJSON_Parse(json_str);
    if (!root)
        return;

    cJSON *data = cJSON_GetObjectItem(root, "data");
    if (!data)
    {
        cJSON_Delete(root);
        return;
    }

    switch (msg->cmd.http_cmd)
    {
    case HTTP_CMD_SET_TIME:
        set_beijing_time(msg,data);
        break;

    default:
        break;
    }
}

void http_recv_msg(WifiMessage_t *msg)
{
    switch (msg->cmd.http_cmd)
    {
    case HTTP_CMD_SET_TIME:
        clock_set_time(&msg->data.clock);
        osSemaphoreRelease(systemInitSemaphore);
        break;

    default:
        break;
    }
}