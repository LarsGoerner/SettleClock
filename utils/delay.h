// SPDX-License-Identifier: MIT
// Copyright (c) 2024 Lars Görner

#ifndef UTILS_DELAY_H_
#define UTILS_DELAY_H_

#include "../hw/hw_defs.h"
#include "../hw/stk.h"
#include "utils.h"

#define USEC_RELOAD_VAL ((MCU_FREQ / 8) / MHz(1))
#define MSEC_RELOAD_VAL ((MCU_FREQ / 8) / KHz(1))

static inline void delay_us(unsigned usecs)
{
        stk_set_clk_src(STK_CLK_SRC_EXT);
        stk_set_reload_val(USEC_RELOAD_VAL);
        stk_clear_cur_val();
        stk_enable_cnt();
        while (usecs--) {
                while (!stk_get_count_flag());
        }
        stk_disable_cnt();
}

static inline void delay_ms(unsigned msecs)
{
#if MSEC_RELOAD_VAL > 0xFFF
        while (msecs--) {
                delay_us(1000);
        }
#else
        stk_set_clk_src(STK_CLK_SRC_EXT);
        stk_set_reload_val(MSEC_RELOAD_VAL);
        stk_clear_cur_val();
        stk_enable_cnt();
        while (msecs--) {
                while (!stk_get_count_flag());
        }
        stk_disable_cnt();
#endif
}

#endif // UTILS_DELAY_H_