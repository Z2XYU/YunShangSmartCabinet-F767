#include "ui_tasks.h"
#include "lcd.h"
#include "touch.h"
#include "dwt.h"
#include "lvgl.h"
#include "../Middlewares/LVGL/GUI/porting/lv_port_disp.h"
#include "../Middlewares/LVGL/GUI/porting/lv_port_indev.h"
#include "../Middlewares/LVGL/GUI/lvgl/src/extra/libs/fsdrv/lv_fsdrv.h"
#include "fatfs.h"
#include "gui_guider.h"
#include "events_init.h"
#include "stdio.h"
#include "sdram.h"

osThreadId_t lvglRefreshTaskHandle;
const osThreadAttr_t lvglRefreshTask_attributes = {
    .name = "lvglRefreshTas",
    .stack_size = 1024 * 4,
    .priority = (osPriority_t)osPriorityAboveNormal,
};


lv_ui guider_ui;

void ui_refresh_tasks_init(void)
{
    lvglRefreshTaskHandle = osThreadNew(lvglRefreshTask, NULL, &lvglRefreshTask_attributes);
}


void lvglRefreshTask(void *argument)
{
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();
    
    //osDelay(1000);
    load_all_image();

    setup_ui(&guider_ui);
    events_init(&guider_ui);
    
    while (1)
    {
        lv_timer_handler();
        osDelay(5);
    }
}