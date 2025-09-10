#include "tasks_init.h"
#include "esp8266.h"
#include "wifi_communication/wifi_tasks.h"
#include "motor_control_tasks.h"
#include "ui_refresh/ui_tasks.h"

void tasks_init(void)
{
    ui_refresh_tasks_init();
    //wifi_communication_tasks_init();
    //motor_control_tasks_init();
}