// SPDX-License-Identifier: MIT
// Copyright (c) 2024 Lars Görner

#ifndef HW_STK_H_
#define HW_STK_H_

#include "../utils/utils.h"

struct systick {
        volatile unsigned CSR;
        volatile unsigned RVR;
        volatile unsigned CVR;
        volatile unsigned CALIB;
};
#define STK ((struct systick *)0xE000E010)

//---| SysTick control & status register

enum stk_clk_src {
        STK_CLK_SRC_EXT,
        STK_CLK_SRC_SYSCLK
};

static inline int stk_get_count_flag(void)
{
        return STK->CSR & BIT(16);
}

static inline void stk_set_clk_src(enum stk_clk_src src)
{
        STK->CSR &= ~BIT(2);
        STK->CSR |= ((src & 1) << 2);
}

static inline void stk_enable_cnt(void)
{
        STK->CSR |= BIT(0);
}

static inline void stk_disable_cnt(void)
{
        STK->CSR &= ~BIT(0);
}

//---| SysTick reload value register

static inline void stk_set_reload_val(unsigned int val)
{
        STK->RVR = val & 0xFFF;
}

//---| SysTick current value register

static inline void stk_clear_cur_val(void)
{
        STK->CVR = 0;
}

//---| SysTick calibration value register

#endif // HW_STK_H_