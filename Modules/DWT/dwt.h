#ifndef __DWT_DELAY_H
#define __DWT_DELAY_H

#include "main.h"

// ------------------ 基础功能 ------------------
void     dwt_init(void);
void     dwt_delay_us(uint32_t us);
void     dwt_delay_ms(uint32_t ms);
void     dwt_delay_ns(uint32_t ns);

// ------------------ Cycle 相关 ------------------
uint32_t dwt_get_cycle(void);
uint32_t dwt_get_delta(uint32_t start, uint32_t end);
uint32_t dwt_cycles_to_us(uint32_t start, uint32_t end);
uint8_t  dwt_is_initialized(void);

// ------------------ Watchpoint 功能 ------------------
void     dwt_set_watchpoint(uint8_t comp_index, uint32_t addr, uint8_t func, uint8_t mask);
void     dwt_clear_watchpoint(uint8_t comp_index);

#endif /* __DWT_DELAY_H */
