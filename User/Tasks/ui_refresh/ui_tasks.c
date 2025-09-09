#include "ui_tasks.h"
#include "lcd.h"
#include "touch.h"
#include "dwt.h"
#include "lvgl.h"
#include "../Middlewares/LVGL/GUI/porting/lv_port_disp.h"
#include "../Middlewares/LVGL/GUI/porting/lv_port_indev.h"
// #include "gui_guider.h"
// #include "events_init.h"

osThreadId_t lvglRefreshTaskHandle; 
const osThreadAttr_t lvglRefreshTask_attributes = {
    .name = "lvglRefreshTas",
    .stack_size = 128 * 12, 
    .priority = (osPriority_t)osPriorityNormal,
};

// lv_ui guider_ui;

void ui_refresh_tasks_init(void)
{
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();

    //  setup_ui(&guider_ui);
    //  events_init(&guider_ui);

    // lvglRefreshTaskHandle =osThreadNew(lvglRefreshTask,NULL,&lvglRefreshTask_attributes);
}

void lvglRefreshTask(void *argument)
{
    while (1)
    {
        lv_timer_handler();
        osDelay(5);
    }
    
}