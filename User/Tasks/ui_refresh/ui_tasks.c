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

osThreadId_t lvglRefreshTaskHandle;
const osThreadAttr_t lvglRefreshTask_attributes = {
    .name = "lvglRefreshTas",
    .stack_size = 128 * 16,
    .priority = (osPriority_t)osPriorityNormal,
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

    // setup_ui(&guider_ui);
    // events_init(&guider_ui);

    /* 创建屏幕 */
    lv_obj_t * scr = lv_scr_act();

    /* 创建图片对象 */
    lv_obj_t * img1 = lv_img_create(scr);

    /* 从 SD 卡直接读取 bin 文件 */
    lv_img_set_src(img1, "0:/a.bin");
    //lv_obj_set_size(img1, 800, 480);

    /* 居中显示 */
    lv_obj_align(img1, LV_ALIGN_CENTER, 0, 0);
    
    while (1)
    {
        lv_timer_handler();
        osDelay(5);
    }
}