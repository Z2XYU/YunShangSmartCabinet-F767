#include "tasks_init.h"
#include "esp8266.h"
#include "wifi_communication/wifi_tasks.h"

void tasks_init(void)
{
    wifi_communication_task_init();
}