/*
 * Copyright 2025 NXP
 * NXP Proprietary. This software is owned or controlled by NXP and may only be used strictly in
 * accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
 * activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
 * terms, then you may not retain, install, activate or otherwise use the software.
 */

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"

int screen_1_digital_clock_1_min_value = 0;
int screen_1_digital_clock_1_hour_value = 0;
int screen_1_digital_clock_1_sec_value = 0;
void setup_scr_screen_1(lv_ui *ui)
{
    // Write codes screen_1
    ui->screen_1 = lv_obj_create(NULL);
    lv_obj_set_size(ui->screen_1, 800, 480);
    lv_obj_set_scrollbar_mode(ui->screen_1, LV_SCROLLBAR_MODE_OFF);

    // Write style for screen_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_1_label_1
    ui->screen_1_label_1 = lv_label_create(ui->screen_1);
    lv_label_set_text(ui->screen_1_label_1, "" LV_SYMBOL_WIFI " ");
    lv_label_set_long_mode(ui->screen_1_label_1, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_1_label_1, 770, 5);
    lv_obj_set_size(ui->screen_1_label_1, 23, 19);

    // Write style for screen_1_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_label_1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_label_1, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_label_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_1_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_label_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_1_label_2
    ui->screen_1_label_2 = lv_label_create(ui->screen_1);
    lv_label_set_text(ui->screen_1_label_2, "" LV_SYMBOL_VOLUME_MAX " ");
    lv_label_set_long_mode(ui->screen_1_label_2, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_1_label_2, 740, 5);
    lv_obj_set_size(ui->screen_1_label_2, 22, 19);

    // Write style for screen_1_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_label_2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_label_2, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_label_2, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_1_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_label_2, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_1_label_3
    ui->screen_1_label_3 = lv_label_create(ui->screen_1);
    lv_label_set_text(ui->screen_1_label_3, "" LV_SYMBOL_GPS " ");
    lv_label_set_long_mode(ui->screen_1_label_3, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_1_label_3, 708, 5);
    lv_obj_set_size(ui->screen_1_label_3, 24, 17);

    // Write style for screen_1_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_label_3, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_label_3, &lv_font_montserrat_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_label_3, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_1_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_label_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_label_3, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_1_heating_img
    ui->screen_1_heating_img = lv_img_create(ui->screen_1);
    lv_obj_add_flag(ui->screen_1_heating_img, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_1_heating_img, "0:/yunshang_images/screen_1/heating.bin");
    // lv_img_set_src(ui->screen_1_heating_img, "0:/yunshang_images/screen_1/heating.bin");
    lv_img_set_pivot(ui->screen_1_heating_img, 50, 50);
    lv_img_set_angle(ui->screen_1_heating_img, 0);
    lv_obj_set_pos(ui->screen_1_heating_img, 28, 299);
    lv_obj_set_size(ui->screen_1_heating_img, 64, 64);

    // Write style for screen_1_heating_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_1_heating_img, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_1_heating_img, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_heating_img, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_1_heating_img, true, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_1_heat_sw
    ui->screen_1_heat_sw = lv_switch_create(ui->screen_1);
    lv_obj_set_pos(ui->screen_1_heat_sw, 40, 388);
    lv_obj_set_size(ui->screen_1_heat_sw, 40, 20);

    // Write style for screen_1_heat_sw, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_heat_sw, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_heat_sw, lv_color_hex(0xe6e2e6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_heat_sw, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_heat_sw, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_heat_sw, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_heat_sw, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for screen_1_heat_sw, Part: LV_PART_INDICATOR, State: LV_STATE_CHECKED.
    lv_obj_set_style_bg_opa(ui->screen_1_heat_sw, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->screen_1_heat_sw, lv_color_hex(0x2195f6), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_heat_sw, LV_GRAD_DIR_NONE, LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_border_width(ui->screen_1_heat_sw, 0, LV_PART_INDICATOR | LV_STATE_CHECKED);

    // Write style for screen_1_heat_sw, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_heat_sw, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_heat_sw, lv_color_hex(0xffffff), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_heat_sw, LV_GRAD_DIR_NONE, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_heat_sw, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_heat_sw, 10, LV_PART_KNOB | LV_STATE_DEFAULT);

    // Write codes screen_1_cooling_img
    ui->screen_1_cooling_img = lv_img_create(ui->screen_1);
    lv_obj_add_flag(ui->screen_1_cooling_img, LV_OBJ_FLAG_CLICKABLE);
    // lv_img_set_src(ui->screen_1_cooling_img, &_cooling_alpha_64x64);
    lv_img_set_src(ui->screen_1_cooling_img, "0:/yunshang_images/screen_1/cooling.bin");
    lv_img_set_pivot(ui->screen_1_cooling_img, 50, 50);
    lv_img_set_angle(ui->screen_1_cooling_img, 0);
    lv_obj_set_pos(ui->screen_1_cooling_img, 133, 299);
    lv_obj_set_size(ui->screen_1_cooling_img, 64, 64);

    // Write style for screen_1_cooling_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_1_cooling_img, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_1_cooling_img, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_cooling_img, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_1_cooling_img, true, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_1_loop_img
    ui->screen_1_loop_img = lv_img_create(ui->screen_1);
    lv_obj_add_flag(ui->screen_1_loop_img, LV_OBJ_FLAG_CLICKABLE);
    // lv_img_set_src(ui->screen_1_loop_img, &_Loop_alpha_64x64);

    lv_img_set_src(ui->screen_1_loop_img, "0:/yunshang_images/screen_1/Loop.bin");
    lv_img_set_pivot(ui->screen_1_loop_img, 50, 50);
    lv_img_set_angle(ui->screen_1_loop_img, 0);
    lv_obj_set_pos(ui->screen_1_loop_img, 238, 299);
    lv_obj_set_size(ui->screen_1_loop_img, 64, 64);

    // Write style for screen_1_loop_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_1_loop_img, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_1_loop_img, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_loop_img, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_1_loop_img, true, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_1_manual_img
    ui->screen_1_manual_img = lv_img_create(ui->screen_1);
    lv_obj_add_flag(ui->screen_1_manual_img, LV_OBJ_FLAG_CLICKABLE);
    // lv_img_set_src(ui->screen_1_manual_img, &_manual_alpha_64x64);
    lv_img_set_src(ui->screen_1_manual_img, "0:/yunshang_images/screen_1/manual.bin");
    lv_img_set_pivot(ui->screen_1_manual_img, 50, 50);
    lv_img_set_angle(ui->screen_1_manual_img, 0);
    lv_obj_set_pos(ui->screen_1_manual_img, 716, 199);
    lv_obj_set_size(ui->screen_1_manual_img, 64, 64);

    // Write style for screen_1_manual_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_1_manual_img, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_1_manual_img, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_manual_img, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_1_manual_img, true, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_1_smart_img
    ui->screen_1_smart_img = lv_img_create(ui->screen_1);
    lv_obj_add_flag(ui->screen_1_smart_img, LV_OBJ_FLAG_CLICKABLE);
    // lv_img_set_src(ui->screen_1_smart_img, &_smart_alpha_64x64);
    lv_img_set_src(ui->screen_1_smart_img, "0:/yunshang_images/screen_1/smart.bin");
    lv_img_set_pivot(ui->screen_1_smart_img, 50, 50);
    lv_img_set_angle(ui->screen_1_smart_img, 0);
    lv_obj_set_pos(ui->screen_1_smart_img, 716, 323);
    lv_obj_set_size(ui->screen_1_smart_img, 64, 64);

    // Write style for screen_1_smart_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_1_smart_img, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_1_smart_img, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_smart_img, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_1_smart_img, true, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_1_automatic_img
    ui->screen_1_automatic_img = lv_img_create(ui->screen_1);
    lv_obj_add_flag(ui->screen_1_automatic_img, LV_OBJ_FLAG_CLICKABLE);
    // lv_img_set_src(ui->screen_1_automatic_img, &_automatic_alpha_64x64);
    lv_img_set_src(ui->screen_1_automatic_img, "0:/yunshang_images/screen_1/automatic.bin");
    lv_img_set_pivot(ui->screen_1_automatic_img, 50, 50);
    lv_img_set_angle(ui->screen_1_automatic_img, 0);
    lv_obj_set_pos(ui->screen_1_automatic_img, 716, 75);
    lv_obj_set_size(ui->screen_1_automatic_img, 64, 64);

    // Write style for screen_1_automatic_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_1_automatic_img, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_1_automatic_img, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_automatic_img, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_1_automatic_img, true, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_1_cool_sw
    ui->screen_1_cool_sw = lv_switch_create(ui->screen_1);
    lv_obj_set_pos(ui->screen_1_cool_sw, 145, 388);
    lv_obj_set_size(ui->screen_1_cool_sw, 40, 20);

    // Write style for screen_1_cool_sw, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_cool_sw, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_cool_sw, lv_color_hex(0xe6e2e6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_cool_sw, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_cool_sw, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_cool_sw, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_cool_sw, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for screen_1_cool_sw, Part: LV_PART_INDICATOR, State: LV_STATE_CHECKED.
    lv_obj_set_style_bg_opa(ui->screen_1_cool_sw, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->screen_1_cool_sw, lv_color_hex(0x2195f6), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_cool_sw, LV_GRAD_DIR_NONE, LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_border_width(ui->screen_1_cool_sw, 0, LV_PART_INDICATOR | LV_STATE_CHECKED);

    // Write style for screen_1_cool_sw, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_cool_sw, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_cool_sw, lv_color_hex(0xffffff), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_cool_sw, LV_GRAD_DIR_NONE, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_cool_sw, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_cool_sw, 10, LV_PART_KNOB | LV_STATE_DEFAULT);

    // Write codes screen_1_digital_clock_1
    static bool screen_1_digital_clock_1_timer_enabled = false;
    ui->screen_1_digital_clock_1 = lv_dclock_create(ui->screen_1, "0:00:00");
    if (!screen_1_digital_clock_1_timer_enabled)
    {
        lv_timer_create(screen_1_digital_clock_1_timer, 1000, NULL);
        screen_1_digital_clock_1_timer_enabled = true;
    }
    lv_obj_set_pos(ui->screen_1_digital_clock_1, 4, 38);
    lv_obj_set_size(ui->screen_1_digital_clock_1, 203, 54);

    // Write style for screen_1_digital_clock_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->screen_1_digital_clock_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_digital_clock_1, lv_color_hex(0x12548b), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_digital_clock_1, &lv_font_Alatsi_Regular_45, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_digital_clock_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_digital_clock_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_digital_clock_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_digital_clock_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_digital_clock_1, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_digital_clock_1, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_digital_clock_1, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_digital_clock_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_digital_clock_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_digital_clock_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_digital_clock_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_1_datetext_1
    ui->screen_1_datetext_1 = lv_label_create(ui->screen_1);
    lv_label_set_text(ui->screen_1_datetext_1, "2025/01/01");
    lv_obj_set_style_text_align(ui->screen_1_datetext_1, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_add_flag(ui->screen_1_datetext_1, LV_OBJ_FLAG_CLICKABLE);
    lv_obj_add_event_cb(ui->screen_1_datetext_1, screen_1_datetext_1_event_handler, LV_EVENT_ALL, NULL);
    lv_obj_set_pos(ui->screen_1_datetext_1, 34, 107);
    lv_obj_set_size(ui->screen_1_datetext_1, 224, 50);

    // Write style for screen_1_datetext_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_radius(ui->screen_1_datetext_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_datetext_1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_datetext_1, &lv_font_Alatsi_Regular_45, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_datetext_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_datetext_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_datetext_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_datetext_1, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_datetext_1, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_datetext_1, 7, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_datetext_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_datetext_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_datetext_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_1_label_4
    ui->screen_1_label_4 = lv_label_create(ui->screen_1);
    lv_label_set_text(ui->screen_1_label_4, "YunShang_IOT");
    lv_label_set_long_mode(ui->screen_1_label_4, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_1_label_4, 192, 8);
    lv_obj_set_size(ui->screen_1_label_4, 416, 41);

    // Write style for screen_1_label_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_label_4, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_label_4, &lv_font_AlexBrush_Regular_40, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_label_4, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_1_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_label_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_label_4, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_1_TH_img
    ui->screen_1_TH_img = lv_img_create(ui->screen_1);
    lv_obj_add_flag(ui->screen_1_TH_img, LV_OBJ_FLAG_CLICKABLE);
    // lv_img_set_src(ui->screen_1_TH_img, &_TH_alpha_64x64);
    lv_img_set_src(ui->screen_1_TH_img, "0:/yunshang_images/screen_1/TH.bin");
    lv_img_set_pivot(ui->screen_1_TH_img, 50, 50);
    lv_img_set_angle(ui->screen_1_TH_img, 0);
    lv_obj_set_pos(ui->screen_1_TH_img, 28, 197);
    lv_obj_set_size(ui->screen_1_TH_img, 64, 64);

    // Write style for screen_1_TH_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_1_TH_img, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_1_TH_img, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_TH_img, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_1_TH_img, true, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_1_label_6
    ui->screen_1_label_6 = lv_label_create(ui->screen_1);
    lv_label_set_text(ui->screen_1_label_6, "0°C");
    lv_label_set_long_mode(ui->screen_1_label_6, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_1_label_6, 114, 204);
    lv_obj_set_size(ui->screen_1_label_6, 149, 49);

    // Write style for screen_1_label_6, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_label_6, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_label_6, &lv_font_Alatsi_Regular_45, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_label_6, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_1_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_label_6, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_label_6, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_1_chart_1
    ui->screen_1_chart_1 = lv_chart_create(ui->screen_1);
    lv_chart_set_type(ui->screen_1_chart_1, LV_CHART_TYPE_LINE);
    lv_chart_set_div_line_count(ui->screen_1_chart_1, 3, 5);
    lv_chart_set_point_count(ui->screen_1_chart_1, 5);
    lv_chart_set_range(ui->screen_1_chart_1, LV_CHART_AXIS_PRIMARY_Y, -20, 60);
    lv_chart_set_axis_tick(ui->screen_1_chart_1, LV_CHART_AXIS_PRIMARY_Y, 10, 5, 9, 1, true, 40);
    lv_chart_set_range(ui->screen_1_chart_1, LV_CHART_AXIS_SECONDARY_Y, 0, 100);
    lv_chart_set_axis_tick(ui->screen_1_chart_1, LV_CHART_AXIS_PRIMARY_X, 10, 5, 5, 4, true, 40);
    lv_chart_set_zoom_x(ui->screen_1_chart_1, 256);
    lv_chart_set_zoom_y(ui->screen_1_chart_1, 256);
    ui->screen_1_chart_1_0 = lv_chart_add_series(ui->screen_1_chart_1, lv_color_hex(0x000000), LV_CHART_AXIS_PRIMARY_Y);
#if LV_USE_FREEMASTER == 0
    lv_chart_set_next_value(ui->screen_1_chart_1, ui->screen_1_chart_1_0, 1);
    lv_chart_set_next_value(ui->screen_1_chart_1, ui->screen_1_chart_1_0, 20);
    lv_chart_set_next_value(ui->screen_1_chart_1, ui->screen_1_chart_1_0, 30);
    lv_chart_set_next_value(ui->screen_1_chart_1, ui->screen_1_chart_1_0, 40);
    lv_chart_set_next_value(ui->screen_1_chart_1, ui->screen_1_chart_1_0, 5);
#endif
    lv_obj_set_pos(ui->screen_1_chart_1, 481, 233);
    lv_obj_set_size(ui->screen_1_chart_1, 205, 155);
    lv_obj_set_scrollbar_mode(ui->screen_1_chart_1, LV_SCROLLBAR_MODE_OFF);

    // Write style for screen_1_chart_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_chart_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_chart_1, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_chart_1, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_chart_1, 1, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_opa(ui->screen_1_chart_1, 45, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_color(ui->screen_1_chart_1, lv_color_hex(0xe8e8e8), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_side(ui->screen_1_chart_1, LV_BORDER_SIDE_BOTTOM | LV_BORDER_SIDE_FULL | LV_BORDER_SIDE_LEFT, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_chart_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_line_width(ui->screen_1_chart_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->screen_1_chart_1, lv_color_hex(0xe8e8e8), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->screen_1_chart_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_chart_1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for screen_1_chart_1, Part: LV_PART_MAIN, State: LV_STATE_FOCUSED.
    lv_obj_set_style_border_width(ui->screen_1_chart_1, 1, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_border_opa(ui->screen_1_chart_1, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_border_color(ui->screen_1_chart_1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_border_side(ui->screen_1_chart_1, LV_BORDER_SIDE_FULL | LV_BORDER_SIDE_LEFT | LV_BORDER_SIDE_BOTTOM, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_opa(ui->screen_1_chart_1, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_color(ui->screen_1_chart_1, lv_color_hex(0xffffff), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_chart_1, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_radius(ui->screen_1_chart_1, 0, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_line_width(ui->screen_1_chart_1, 2, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_line_color(ui->screen_1_chart_1, lv_color_hex(0xd0d0d0), LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_line_opa(ui->screen_1_chart_1, 255, LV_PART_MAIN | LV_STATE_FOCUSED);
    lv_obj_set_style_shadow_width(ui->screen_1_chart_1, 0, LV_PART_MAIN | LV_STATE_FOCUSED);

    // Write style for screen_1_chart_1, Part: LV_PART_TICKS, State: LV_STATE_DEFAULT.
    lv_obj_set_style_text_color(ui->screen_1_chart_1, lv_color_hex(0x151212), LV_PART_TICKS | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_chart_1, &lv_font_simsun_16, LV_PART_TICKS | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_chart_1, 255, LV_PART_TICKS | LV_STATE_DEFAULT);
    lv_obj_set_style_line_width(ui->screen_1_chart_1, 2, LV_PART_TICKS | LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->screen_1_chart_1, lv_color_hex(0xe8e8e8), LV_PART_TICKS | LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->screen_1_chart_1, 255, LV_PART_TICKS | LV_STATE_DEFAULT);

    // Write codes screen_1_label_7
    ui->screen_1_label_7 = lv_label_create(ui->screen_1);
    lv_label_set_text(ui->screen_1_label_7, "0%");
    lv_label_set_long_mode(ui->screen_1_label_7, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_1_label_7, 283, 206);
    lv_obj_set_size(ui->screen_1_label_7, 145, 45);

    // Write style for screen_1_label_7, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_label_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_label_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_label_7, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_label_7, &lv_font_Alatsi_Regular_45, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_label_7, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_label_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_1_label_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_label_7, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_label_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_label_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_label_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_label_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_label_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_label_7, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_1_plasma_img
    ui->screen_1_plasma_img = lv_img_create(ui->screen_1);
    lv_obj_add_flag(ui->screen_1_plasma_img, LV_OBJ_FLAG_CLICKABLE);
    // lv_img_set_src(ui->screen_1_plasma_img, &_plasma_alpha_64x64);
    lv_img_set_src(ui->screen_1_plasma_img, "0:/yunshang_images/screen_1/plasma.bin");
    lv_img_set_pivot(ui->screen_1_plasma_img, 50, 50);
    lv_img_set_angle(ui->screen_1_plasma_img, 0);
    lv_obj_set_pos(ui->screen_1_plasma_img, 343, 299);
    lv_obj_set_size(ui->screen_1_plasma_img, 64, 64);

    // Write style for screen_1_plasma_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_1_plasma_img, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_1_plasma_img, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_plasma_img, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_1_plasma_img, true, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_1_loop_sw
    ui->screen_1_loop_sw = lv_switch_create(ui->screen_1);
    lv_obj_set_pos(ui->screen_1_loop_sw, 250, 388);
    lv_obj_set_size(ui->screen_1_loop_sw, 40, 20);

    // Write style for screen_1_loop_sw, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_loop_sw, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_loop_sw, lv_color_hex(0xe6e2e6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_loop_sw, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_loop_sw, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_loop_sw, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_loop_sw, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for screen_1_loop_sw, Part: LV_PART_INDICATOR, State: LV_STATE_CHECKED.
    lv_obj_set_style_bg_opa(ui->screen_1_loop_sw, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->screen_1_loop_sw, lv_color_hex(0x2195f6), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_loop_sw, LV_GRAD_DIR_NONE, LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_border_width(ui->screen_1_loop_sw, 0, LV_PART_INDICATOR | LV_STATE_CHECKED);

    // Write style for screen_1_loop_sw, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_loop_sw, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_loop_sw, lv_color_hex(0xffffff), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_loop_sw, LV_GRAD_DIR_NONE, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_loop_sw, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_loop_sw, 10, LV_PART_KNOB | LV_STATE_DEFAULT);

    // Write codes screen_1_plasma_sw
    ui->screen_1_plasma_sw = lv_switch_create(ui->screen_1);
    lv_obj_set_pos(ui->screen_1_plasma_sw, 355, 388);
    lv_obj_set_size(ui->screen_1_plasma_sw, 40, 20);

    // Write style for screen_1_plasma_sw, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_plasma_sw, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_plasma_sw, lv_color_hex(0xe6e2e6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_plasma_sw, LV_GRAD_DIR_NONE, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_plasma_sw, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_plasma_sw, 10, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_plasma_sw, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write style for screen_1_plasma_sw, Part: LV_PART_INDICATOR, State: LV_STATE_CHECKED.
    lv_obj_set_style_bg_opa(ui->screen_1_plasma_sw, 255, LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(ui->screen_1_plasma_sw, lv_color_hex(0x2195f6), LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_plasma_sw, LV_GRAD_DIR_NONE, LV_PART_INDICATOR | LV_STATE_CHECKED);
    lv_obj_set_style_border_width(ui->screen_1_plasma_sw, 0, LV_PART_INDICATOR | LV_STATE_CHECKED);

    // Write style for screen_1_plasma_sw, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
    lv_obj_set_style_bg_opa(ui->screen_1_plasma_sw, 255, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui->screen_1_plasma_sw, lv_color_hex(0xffffff), LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_grad_dir(ui->screen_1_plasma_sw, LV_GRAD_DIR_NONE, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_border_width(ui->screen_1_plasma_sw, 0, LV_PART_KNOB | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_plasma_sw, 10, LV_PART_KNOB | LV_STATE_DEFAULT);

    // Write codes screen_1_label_8
    ui->screen_1_label_8 = lv_label_create(ui->screen_1);
    lv_label_set_text(ui->screen_1_label_8, "--ZhongXu");
    lv_label_set_long_mode(ui->screen_1_label_8, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_1_label_8, 643, 442);
    lv_obj_set_size(ui->screen_1_label_8, 151, 29);

    // Write style for screen_1_label_8, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_label_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_label_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_label_8, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_label_8, &lv_font_AlexBrush_Regular_40, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_label_8, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_label_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_1_label_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_label_8, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_label_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_label_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_label_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_label_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_label_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_label_8, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    //Write codes screen_1_location_img
    ui->screen_1_location_img = lv_img_create(ui->screen_1);
    lv_obj_add_flag(ui->screen_1_location_img, LV_OBJ_FLAG_CLICKABLE);
    lv_img_set_src(ui->screen_1_location_img, &_locatiom_alpha_200x150);
    //lv_img_set_src(ui->screen_1_location_img, "0:/yunshang_images/screen_1/location.bin");
    //lv_img_set_src(ui->screen_1_location_img, &images[1].dsc);
    lv_img_set_pivot(ui->screen_1_location_img, 50,50);
    lv_img_set_angle(ui->screen_1_location_img, 0);
    lv_obj_set_pos(ui->screen_1_location_img, 472, 67);
    lv_obj_set_size(ui->screen_1_location_img, 200, 150);

    // Write style for screen_1_location_img, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_img_recolor_opa(ui->screen_1_location_img, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_img_opa(ui->screen_1_location_img, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_location_img, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_clip_corner(ui->screen_1_location_img, true, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_1_label_9
    ui->screen_1_label_9 = lv_label_create(ui->screen_1);
    lv_label_set_text(ui->screen_1_label_9, "我们在这儿~");
    lv_label_set_long_mode(ui->screen_1_label_9, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_1_label_9, 283, 75);
    lv_obj_set_size(ui->screen_1_label_9, 151, 23);

    // Write style for screen_1_label_9, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_label_9, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_label_9, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_label_9, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_label_9, &lv_font_simsun_20, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_label_9, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_label_9, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_1_label_9, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_label_9, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_label_9, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_label_9, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_label_9, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_label_9, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_label_9, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_label_9, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_1_label_10
    ui->screen_1_label_10 = lv_label_create(ui->screen_1);
    lv_label_set_text(ui->screen_1_label_10, "" LV_SYMBOL_GPS "  洛龙区学子街8号");
    lv_label_set_long_mode(ui->screen_1_label_10, LV_LABEL_LONG_WRAP);
    lv_obj_set_pos(ui->screen_1_label_10, 287, 139);
    lv_obj_set_size(ui->screen_1_label_10, 161, 20);

    // Write style for screen_1_label_10, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_border_width(ui->screen_1_label_10, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_radius(ui->screen_1_label_10, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_color(ui->screen_1_label_10, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_font(ui->screen_1_label_10, &lv_font_simsun_16, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui->screen_1_label_10, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_letter_space(ui->screen_1_label_10, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_line_space(ui->screen_1_label_10, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui->screen_1_label_10, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui->screen_1_label_10, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_top(ui->screen_1_label_10, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_right(ui->screen_1_label_10, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_bottom(ui->screen_1_label_10, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_pad_left(ui->screen_1_label_10, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_shadow_width(ui->screen_1_label_10, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    // Write codes screen_1_line_1
    ui->screen_1_line_1 = lv_line_create(ui->screen_1);
    static lv_point_t screen_1_line_1[] = {
        {0, 0},
        {200, 60},
    };
    lv_line_set_points(ui->screen_1_line_1, screen_1_line_1, 2);
    lv_obj_set_pos(ui->screen_1_line_1, 375, 99);
    lv_obj_set_size(ui->screen_1_line_1, 161, 60);

    // Write style for screen_1_line_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
    lv_obj_set_style_line_width(ui->screen_1_line_1, 2, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_line_color(ui->screen_1_line_1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_line_opa(ui->screen_1_line_1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_line_rounded(ui->screen_1_line_1, true, LV_PART_MAIN | LV_STATE_DEFAULT);

    // The custom code of screen_1.

    // Update current screen layout.
    lv_obj_update_layout(ui->screen_1);
}
