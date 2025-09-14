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

/* 动画执行回调函数 */
static void bar_anim_cb(void *var,int32_t v)
{
    lv_obj_t *bar = (lv_obj_t *)var;
    lv_bar_set_value(bar,v,LV_ANIM_OFF);
}
/* 动画完成后的回调函数 */
static void bar_anim_ready(lv_anim_t *a)
{
    ui_load_scr_animation(&guider_ui,&guider_ui.screen_1,
                            guider_ui.screen_1_del,&guider_ui.screen_del,
                            setup_scr_screen_1,LV_SCR_LOAD_ANIM_FADE_ON,
                            0,0,true,true);
}
/* 加载动画 */
 void laod_bar_anim(void)
 {
    lv_anim_t a;
    lv_anim_init(&a);

    lv_anim_set_var(&a,guider_ui.screen_bar_1);
    lv_anim_set_values(&a,0,100);

    lv_anim_set_time(&a,3000);
    lv_anim_set_exec_cb(&a,bar_anim_cb);
    lv_anim_set_ready_cb(&a,bar_anim_ready);
    lv_anim_start(&a);
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

