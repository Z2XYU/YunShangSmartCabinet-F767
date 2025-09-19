#include "images_load.h"
#include "fatfs.h"
#include "sdmmc.h"
#include "stdio.h"

#define IMG_NUM 1
uint8_t background_img[800 * 480 * 2] __attribute__((section(".sdram_data")));
// uint8_t location_img[600 * 450 * 2] __attribute__((section(".sdram_data")));

ImageRes_t images[] = {
    {"0:/background.bin", 800, 480, {{0}}, background_img},
    //{"0:/yunshang_images/screen_1/location.bin", 600, 450, {{0}}, location_img}
};

static int image_load_to_sdram(ImageRes_t *img)
{
    if (img->buf == NULL)
        return -3; // SDRAM 地址非法

    static FIL file;
    static UINT br;
    static FRESULT res;

    uint32_t size = img->width * img->height * 2; // RGB565

    res = f_open(&file, img->path, FA_READ);
    if (res != FR_OK)
    {
        // printf("open %s failed res=%d\r\n", img->path, res);
        return -1;
    }

    res = f_read(&file, img->buf, size, &br);

    f_close(&file);
    while (HAL_SD_GetCardState(&hsd1) != HAL_SD_CARD_TRANSFER)
        ;

    // 填充 img 描述符
    img->dsc.header.always_zero = 0;
    img->dsc.header.w = img->width;
    img->dsc.header.h = img->height;
    img->dsc.header.cf = LV_IMG_CF_TRUE_COLOR;
    img->dsc.data_size = size;
    img->dsc.data = img->buf;

    return 0;
}

void load_all_image(void)
{
    // printf("background_img addr = 0x%08X\r\n", (unsigned int)background_img);
    // printf("location_img  addr = 0x%08X\r\n", (unsigned int)location_img);
    for (int i = 0; i < IMG_NUM; i++)
    {
        if (images[i].buf == NULL)
        {
            // printf("image %d buffer not assigned\n", i);
            continue;
        }
        if (image_load_to_sdram(&images[i]) == 0)
        {
            // printf("加载 image%d 成功\r\n", i);
        }
        else
        {
            // printf("加载 image%d 失败\r\n", i);
        }
    }
}