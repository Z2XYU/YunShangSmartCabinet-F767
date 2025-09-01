#include "dwt.h"

// ------------------ 常量定义 ------------------
#define DWT_LAR_KEY     0xC5ACCE55   // 解锁 DWT 的 key
#define DEMCR_TRCENA    (1 << 24)    // DEMCR 中 TRCENA 位置

// ------------------ 全局变量 ------------------
static uint8_t dwt_initialized = 0;  // 标记是否已初始化

// ------------------ 基础功能 ------------------

/**
 * @brief  初始化 DWT（Data Watchpoint and Trace）
 * 
 * - 开启 DWT 功能
 * - 解锁 DWT 寄存器
 * - 清零并启动 cycle counter
 */
void dwt_init(void)
{
    CoreDebug->DEMCR |= DEMCR_TRCENA;   // 使能 DWT
    DWT->LAR = DWT_LAR_KEY;             // 解锁寄存器（部分芯片需要）
    DWT->CYCCNT = 0;                    // 清零 cycle counter
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;// 启用 cycle counter
    dwt_initialized = 1;
}

/**
 * @brief  微秒级延时
 * @param  us 延时时间（单位: us）
 */
void dwt_delay_us(uint32_t us)
{
    if (!dwt_initialized) dwt_init();

    uint32_t start = DWT->CYCCNT;
    uint32_t ticks = us * (HAL_RCC_GetHCLKFreq() / 1000000U);

    while ((uint32_t)(DWT->CYCCNT - start) < ticks);
}

/**
 * @brief  毫秒级延时
 * @param  ms 延时时间（单位: ms）
 */
void dwt_delay_ms(uint32_t ms)
{
    while (ms--)
    {
        dwt_delay_us(1000);
    }
}

/**
 * @brief  纳秒级延时（近似）
 * @param  ns 延时时间（单位: ns）
 */
void dwt_delay_ns(uint32_t ns)
{
    if (!dwt_initialized) dwt_init();

    uint32_t start = DWT->CYCCNT;
    uint32_t ticks = (uint64_t)ns * (HAL_RCC_GetHCLKFreq() / 1000000000U);

    while ((uint32_t)(DWT->CYCCNT - start) < ticks);
}

// ------------------ Cycle 相关功能 ------------------

/**
 * @brief  获取当前 cycle counter 值
 * @return 当前计数值
 */
uint32_t dwt_get_cycle(void)
{
    if (!dwt_initialized) dwt_init();
    return DWT->CYCCNT;
}

/**
 * @brief  计算两个 cycle counter 之间的差值
 * @param  start 起始 cycle
 * @param  end   结束 cycle
 * @return 差值（单位: cycles）
 */
uint32_t dwt_get_delta(uint32_t start, uint32_t end)
{
    return (uint32_t)(end - start);
}

/**
 * @brief  将 cycle 差值转换为微秒
 * @param  start 起始 cycle
 * @param  end   结束 cycle
 * @return 时间差（单位: us）
 */
uint32_t dwt_cycles_to_us(uint32_t start, uint32_t end)
{
    uint32_t delta = dwt_get_delta(start, end);
    return delta / (HAL_RCC_GetHCLKFreq() / 1000000U);
}

/**
 * @brief  判断 DWT 是否已初始化
 * @return 1 已初始化，0 未初始化
 */
uint8_t dwt_is_initialized(void)
{
    return dwt_initialized;
}

// ------------------ Watchpoint 功能 ------------------

/**
 * @brief  设置一个 DWT Watchpoint（数据访问断点）
 * @param  comp_index 比较寄存器编号 (0~3)
 * @param  addr       要监视的地址
 * @param  func       功能选择
 *         - 0x4  仅写触发
 *         - 0x5  仅读触发
 *         - 0x6  读写都触发
 * @param  mask       地址掩码（2^mask 字节范围）
 *         - 0 = 精确地址
 *         - 1 = 2 字节对齐
 *         - 2 = 4 字节范围
 *         - 3 = 8 字节范围 ...
 */
void dwt_set_watchpoint(uint8_t comp_index, uint32_t addr, uint8_t func, uint8_t mask)
{
    if (!dwt_initialized) dwt_init();

    // COMPn, MASKn, FUNCTIONn 的地址间隔为 0x10
    volatile uint32_t *COMP     = &DWT->COMP0     + comp_index * 3;
    volatile uint32_t *MASK     = &DWT->MASK0     + comp_index * 3;
    volatile uint32_t *FUNCTION = &DWT->FUNCTION0 + comp_index * 3;

    *COMP     = addr;
    *MASK     = mask;
    *FUNCTION = func;
}

/**
 * @brief  清除 DWT Watchpoint
 * @param  comp_index 比较寄存器编号 (0~3)
 */
void dwt_clear_watchpoint(uint8_t comp_index)
{
    volatile uint32_t *FUNCTION = &DWT->FUNCTION0 + comp_index * 3;
    *FUNCTION = 0; // 清零即可关闭
}
