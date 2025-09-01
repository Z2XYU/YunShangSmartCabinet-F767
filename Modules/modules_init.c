#include "modules_init.h"
#include "dwt.h"
#include "sdram.h"
#include "soft_iic.h"
#include "mpu.h"

void modeules_init(void)
{
    dwt_init();
    sdram_init();
    mpu_memory_protection();
    iic_init();
}