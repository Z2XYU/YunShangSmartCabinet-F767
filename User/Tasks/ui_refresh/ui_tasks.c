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
#include "env_meas_tasks.h"
#include "custom.h"
#include "sh40.h"

osThreadId_t lvglRefreshTaskHandle;
const osThreadAttr_t lvglRefreshTask_attributes = {
    .name = "lvglRefreshTask",
    .stack_size = 1024 * 4,
    .priority = (osPriority_t)osPriorityAboveNormal,
};

lv_ui guider_ui;

osSemaphoreId_t systemInitSemaphore;

void ui_refresh_tasks_init(void)
{
    systemInitSemaphore = osSemaphoreNew(1,0,NULL);
    lvglRefreshTaskHandle = osThreadNew(lvglRefreshTask, NULL, &lvglRefreshTask_attributes);
}

static void ui_temperature_humidity_refresh(SH40_t *sh40_sensor)
{
    if (guider_ui.screen_1_label_6 != NULL)
    {
        lv_label_set_text_fmt(guider_ui.screen_1_label_6, "%.1f°C", sh40_sensor->temperature);
    }
    if (guider_ui.screen_1_label_7 != NULL)
    {
        lv_label_set_text_fmt(guider_ui.screen_1_label_7, "%.1f%%", sh40_sensor->humidity);
    }
}

static void ui_prama_refresh_cb(lv_timer_t *timer)
{
    LV_UNUSED(timer);
    if (osMutexAcquire(sh40MeasMutexHandle, 5) == osOK)
    {
        ui_temperature_humidity_refresh(&sh40_sensor);
        osMutexRelease(sh40MeasMutexHandle);
    }
}

void lvglRefreshTask(void *argument)
{
    lv_init();
    lv_port_disp_init();
    lv_port_indev_init();

    load_all_image();

    setup_ui(&guider_ui);
    events_init(&guider_ui);

    lv_timer_create(ui_prama_refresh_cb, 1000, NULL);

    while (1)
    {
        if (osSemaphoreAcquire(systemInitSemaphore, 0) == osOK)
        {
            ui_load_scr_animation(&guider_ui, &guider_ui.screen_1,
                                  guider_ui.screen_1_del, &guider_ui.screen_del,
                                  setup_scr_screen_1, LV_SCR_LOAD_ANIM_FADE_ON,
                                  0, 0, true, true);
                printf("切换\n");
        }
        lv_timer_handler();
        osDelay(5);
    }
}