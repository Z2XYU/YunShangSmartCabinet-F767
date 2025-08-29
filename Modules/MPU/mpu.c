#include "dwt_delay.h"
#include "mpu.h"

/**
 * @brief       设置某个区域的MPU保护
 * @param       baseaddr: MPU保护区域的基址(首地址)
 * @param       size:MPU保护区域的大小(必须是32的倍数,单位为字节)
 * @param       rnum:MPU保护区编号,范围:0~7,最大支持8个保护区域
 * @param       de:禁止指令访问;0,允许指令访问;1,禁止指令访问
 * @param       ap:访问权限,访问关系如下:
 *   @arg       0,无访问（特权&用户都不可访问）
 *   @arg       1,仅支持特权读写访问
 *   @arg       2,禁止用户写访问（特权可读写访问）
 *   @arg       3,全访问（特权&用户都可访问）
 *   @arg       4,无法预测(禁止设置为4!!!)
 *   @arg       5,仅支持特权读访问
 *   @arg       6,只读（特权&用户都不可以写）
 *   @note      详见:STM32F7编程手册.pdf,4.6节,Table 89.
 * @param       sen:是否允许共用;0,不允许;1,允许
 * @param       cen:是否允许cache;0,不允许;1,允许
 * @param       ben:是否允许缓冲;0,不允许;1,允许
 * @retval      0, 成功; 1, 错误;
 */
uint8_t mpu_set_protection(uint32_t baseaddr, uint32_t size, uint32_t rnum, uint8_t de, uint8_t ap, uint8_t sen, uint8_t cen, uint8_t ben)
{
    MPU_Region_InitTypeDef mpu_region_init_struct; /* MPU初始化句柄 */
    HAL_MPU_Disable();                             /* 配置MPU之前先关闭MPU,配置完成以后在使能MPU */

    mpu_region_init_struct.Enable = MPU_REGION_ENABLE;    /* 使能该保护区域 */
    mpu_region_init_struct.Number = rnum;                 /* 设置保护区域 */
    mpu_region_init_struct.BaseAddress = baseaddr;        /* 设置基址 */
    mpu_region_init_struct.Size = size;                   /* 设置保护区域大小 */
    mpu_region_init_struct.SubRegionDisable = 0X00;       /* 禁止子区域 */
    mpu_region_init_struct.TypeExtField = MPU_TEX_LEVEL0; /* 设置类型扩展域为level0 */
    mpu_region_init_struct.DisableExec = de;              /* 是否允许指令访问(允许读取指令) */
    mpu_region_init_struct.AccessPermission = ap;         /* 设置访问权限 */
    mpu_region_init_struct.IsShareable = sen;             /* 是否允许共用 */
    mpu_region_init_struct.IsCacheable = cen;             /* 是否允许cache */
    mpu_region_init_struct.IsBufferable = ben;            /* 是否允许缓冲 */
    HAL_MPU_ConfigRegion(&mpu_region_init_struct);        /* 配置MPU */
    HAL_MPU_Enable(MPU_PRIVILEGED_DEFAULT);               /* 开启MPU */
    return 0;
}

/**
 * @brief       设置需要保护的存储块
 * @note        必须对部分存储区域进行MPU保护,否则可能导致程序运行异常
 *              比如MCU屏不显示,摄像头采集数据出错等等问题
 * @param       无
 * @retval      无
 */
void mpu_memory_protection(void)
{
    /*保护SDRAM区域,共32M字节,允许指令访问,允许共用,允许cache,允许缓冲 */
    mpu_set_protection(0XC0000000, MPU_REGION_SIZE_32MB, MPU_REGION_NUMBER2, MPU_INSTRUCTION_ACCESS_ENABLE,
                       MPU_REGION_FULL_ACCESS, MPU_ACCESS_SHAREABLE, MPU_ACCESS_CACHEABLE, MPU_ACCESS_BUFFERABLE);
}
