#include "lvgl_image.h"
#include "fatfs.h"
#include "sdmmc.h"
#include "stdio.h"

#define IMG_NUM 1
#define SDRAM_BASE 0xC0000000
#define DISP_BUF_SIZE (800 * 480 * 2)
#define DISP_BUF_NUM 3
#define SDRAM_IMG_ADDR (SDRAM_BASE + DISP_BUF_SIZE * DISP_BUF_NUM) // 0xC0023240
#define SDRAM_TOTAL_SIZE (32U * 1024U * 1024U)
#define SDRAM_END_ADDR (0xC0000000 + SDRAM_TOTAL_SIZE)

ImageRes_t images[] = {
    {"0:/images/image1.bin", 800, 480, {{0}}, NULL},
    // {"0:/images/image2.bin", 207, 288, {{0}}, NULL},
    // {"0:/images/image3.bin", 142, 100, {{0}}, NULL}
};

static void image_assign_buf(void)
{
    uint32_t addr = SDRAM_IMG_ADDR;

    for (int i = 0; i < IMG_NUM; i++)
    {
        uint32_t size = images[i].width * images[i].height * 2;

        addr = (addr + 3) & ~3;

        if ((addr + size) > SDRAM_END_ADDR)
        {
            printf("SDRAM overflow!\n");
            images[i].buf = NULL; // 标记失败
            continue;
        }

        images[i].buf = (uint8_t *)addr;
        addr += size;
        printf("image%d buf=%p\n", i, images[i].buf);
    }
}

static int image_load_to_sdram(ImageRes_t *img)
{
    if (img->buf == NULL)
        return -3; // SDRAM 地址非法

    static  FIL file;
    static  UINT br;
    static  FRESULT res;

    uint32_t size = img->width * img->height * 2; // RGB565

    res = f_open(&file, img->path, FA_READ);
    if (res != FR_OK)
    {
        printf("open %s failed res=%d\r\n", img->path, res);
        return -1;
    }

    res = f_read(&file,img->buf,size,&br);

    f_close(&file);
    while (HAL_SD_GetCardState(&hsd1) != HAL_SD_CARD_TRANSFER);

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
    image_assign_buf();

    for (int i = 0; i < IMG_NUM; i++)
    {
        if (images[i].buf == NULL)
        {
            printf("image %d buffer not assigned\n", i);
            continue;
        }

        if (image_load_to_sdram(&images[i]) == 0)
            printf("加载 image%d 成功\r\n", i);
        else
            printf("加载 image%d 失败\r\n", i);
    }
}