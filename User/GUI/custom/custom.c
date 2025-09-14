/*
* Copyright 2023 NXP
* NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/


/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include "lvgl.h"
#include "custom.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/* 加载动画 */
static void bar_anim_ready(lv_timer_t * timer)
{
    LV_UNUSED(timer);
    ui_load_scr_animation(&guider_ui,&guider_ui.screen_1,
                            guider_ui.screen_1_del,&guider_ui.screen_del,
                            setup_scr_screen_1,LV_SCR_LOAD_ANIM_FADE_ON,
                            0,0,true,true);
}

void laod_bar_anim(void)
{
   // 3 秒后执行切换
    lv_timer_t * t = lv_timer_create(bar_anim_ready, 3000, NULL);
    lv_timer_set_repeat_count(t, 1);  // 执行一次
}
/**********************
 *  STATIC VARIABLES
 **********************/

/**
 * Create a demo application
 */

void custom_init(lv_ui *ui)
{
    /* Add your codes here */
    laod_bar_anim();
}

