#pragma once

#include "main.h"
#include "lvgl.h"

typedef struct
{
    const char* path;
    uint16_t width;
    uint16_t height;
    lv_img_dsc_t dsc;
    uint8_t *buf;
}ImageRes_t;

extern ImageRes_t images[];

void load_all_image(void);