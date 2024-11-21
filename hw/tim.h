// SPDX-License-Identifier: MIT
// Copyright (c) 2024 Lars Görner

#ifndef HW_TIM_H_
#define HW_TIM_H_

#include "../utils/utils.h"

struct tim {
        volatile unsigned CR1;
        volatile unsigned CR2;
        volatile unsigned SMCR;
        volatile unsigned DIER;
        volatile unsigned SR;
        volatile unsigned EGR;
        volatile unsigned CCMR1;
        volatile unsigned CCMR2;
        volatile unsigned CCER;
        volatile unsigned CNT;
        volatile unsigned PSC;
        volatile unsigned ARR;
        volatile unsigned RCR;
        volatile unsigned CCR1;
        volatile unsigned CCR2;
        volatile unsigned CCR3;
        volatile unsigned CCR4;
        volatile unsigned BDTR;
        volatile unsigned DCR;
        volatile unsigned DMAR;
};
#define TIM3    ((struct tim *)0x40000400)
#define TIM6    ((struct tim *)0x40001000)
#define TIM7    ((struct tim *)0x40001400)
#define TIM14   ((struct tim *)0x40002000)
#define TIM15   ((struct tim *)0x40014000)
#define TIM16   ((struct tim *)0x40014400)
#define TIM17   ((struct tim *)0x40014800)

//--------------------------------| TIM_CR1 |---------------------------------//

enum tim_dir {
        TIM_DIR_UP,
        TIM_DIR_DOWN
};

enum tim_urs {
        TIM_URS_ALL,
        TIM_URS_OV_UV
};

struct tim_cr1_init {
        union {
                struct {
                        unsigned cen        : 1;
                        unsigned udis       : 1;
                        enum tim_urs urs : 1;
                        unsigned opm        : 1;
                        uint8_t         : 3;
                        unsigned arpe       : 1;
                };
                unsigned reg_val;
        };
};

static inline void tim_init_cr1(struct tim * tim, struct tim_cr1_init init)
{
        tim->CR1 = init.reg_val;
}

static inline void tim_enable_cnt(struct tim * tim)
{
        BIT_SET(tim->CR1, 0);
}

static inline void tim_disable_cnt(struct tim * tim)
{
        BIT_CLR(tim->CR1, 0);
}

static inline void tim_set_urs(struct tim * tim, enum tim_urs urs)
{
        BIT_WRITE(tim->CR1, urs, 2);
}

static inline void tim_enable_opm(struct tim * tim)
{
        BIT_SET(tim->CR1, 3);
}

static inline void tim_disable_opm(struct tim * tim)
{
        BIT_CLR(tim->CR1, 3);
}

static inline void tim_set_dir(struct tim * tim, enum tim_dir dir)
{
        BIT_WRITE(tim->CR1, dir, 4);
}

//--------------------------------| TIM_CR2 |---------------------------------//



//--------------------------------| TIM_SMCR |--------------------------------//

//--------------------------------| TIM_DIER |--------------------------------//

//---------------------------------| TIM_SR |---------------------------------//

static inline int tim_is_update_interrupt(struct tim * tim)
{
        return tim->SR & BIT(0);
}

static inline void tim_clear_update_interrupt(struct tim * tim)
{
        BIT_CLR(tim->SR, 0);
}

//--------------------------------| TIM_ERG |---------------------------------//
//-------------------------------| TIM_CCMR1 |--------------------------------//
//-------------------------------| TIM_CCMR2 |--------------------------------//
//--------------------------------| TIM_CCER |--------------------------------//
//--------------------------------| TIM_CNT |---------------------------------//

static inline void tim_reset_cnt(struct tim * tim)
{
        tim->CNT = 0;
}

//--------------------------------| TIM_PSC |---------------------------------//

static inline void tim_set_psc(struct tim * tim, unsigned psc)
{
        tim->PSC = psc - 1;
}

//--------------------------------| TIM_ARR |---------------------------------//

static inline void tim_set_arr(struct tim * tim, unsigned ar)
{
        tim->ARR = ar - 1;
}

//--------------------------------| TIM_RCR |---------------------------------//
//--------------------------------| TIM_CCR1 |--------------------------------//
//--------------------------------| TIM_CCR2 |--------------------------------//
//--------------------------------| TIM_CCR3 |--------------------------------//
//--------------------------------| TIM_CCR4 |--------------------------------//
//--------------------------------| TIM_BDTR |--------------------------------//
//--------------------------------| TIM_DCR |---------------------------------//
//--------------------------------| TIM_DMAR |--------------------------------//


#endif // HW_TIM_H_