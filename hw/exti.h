/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2024 Lars Görner */

#ifndef HW_EXTI_H_
#define HW_EXTI_H_

#include "../utils/utils.h"

/** @brief EXTI register */
struct exti {
        volatile unsigned IMR;
        volatile unsigned EMR;
        volatile unsigned RTSR;
        volatile unsigned FTSR;
        volatile unsigned SWIER;
        volatile unsigned PR;
};
#define EXTI ((struct exti *)0x40010400)

#define EXTI_LINE_0     BIT(0)
#define EXTI_LINE_1     BIT(1)
#define EXTI_LINE_2     BIT(2)
#define EXTI_LINE_3     BIT(3)
#define EXTI_LINE_4     BIT(4)
#define EXTI_LINE_5     BIT(5)
#define EXTI_LINE_6     BIT(6)
#define EXTI_LINE_7     BIT(7)
#define EXTI_LINE_8     BIT(8)
#define EXTI_LINE_9     BIT(9)
#define EXTI_LINE_10    BIT(10)
#define EXTI_LINE_11    BIT(11)
#define EXTI_LINE_12    BIT(12)
#define EXTI_LINE_13    BIT(13)
#define EXTI_LINE_14    BIT(14)
#define EXTI_LINE_15    BIT(15)
#define EXTI_LINE_16    BIT(16)
#define EXTI_LINE_17    BIT(17)
#define EXTI_LINE_18    BIT(18)
#define EXTI_LINE_19    BIT(19)
#define EXTI_LINE_20    BIT(20)
#define EXTI_LINE_21    BIT(21)
#define EXTI_LINE_22    BIT(22)
#define EXTI_LINE_23    BIT(23)
#define EXTI_LINE_24    BIT(24)
#define EXTI_LINE_25    BIT(25)
#define EXTI_LINE_26    BIT(26)
#define EXTI_LINE_27    BIT(27)
#define EXTI_LINE_28    BIT(28)
#define EXTI_LINE_29    BIT(29)
#define EXTI_LINE_30    BIT(30)
#define EXTI_LINE_31    BIT(31)

//--------------------------------| EXTI_IMR |--------------------------------//

static inline void exti_enable_line_interrupt(unsigned lines)
{
        EXTI->IMR |= lines;
}

static inline void exti_disable_line_interrupt(unsigned lines)
{
        EXTI->IMR &= ~lines;
}

//--------------------------------| EXTI_EMR |--------------------------------//

static inline void exti_enable_line_event(unsigned lines)
{
        EXTI->EMR |= lines;
}

static inline void exti_disable_line_event(unsigned lines)
{
        EXTI->EMR &= ~lines;
}

//--------------------------------| EXTI_RTSR |-------------------------------//

static inline void exti_enable_rising_trigger_event(unsigned lines)
{
        EXTI->RTSR |= lines;
}

static inline void exti_disable_rising_trigger_event(unsigned lines)
{
        EXTI->RTSR &= ~lines;
}

//--------------------------------| EXTI_FTSR |-------------------------------//

static inline void exti_enable_falling_trigger_event(unsigned lines)
{
        EXTI->FTSR |= lines;
}

static inline void exti_disable_falling_trigger_event(unsigned lines)
{
        EXTI->FTSR &= ~lines;
}

//-------------------------------| EXTI_SWIER |-------------------------------//

static inline void exti_trigger_event(unsigned lines)
{
        EXTI->SWIER |= lines;
}

//-------------------------------| EXTI_SWIER |-------------------------------//

static inline int exti_pending(unsigned lines)
{
        return EXTI->PR & lines;
}

static inline int exti_ack_pending(unsigned lines)
{
        return EXTI->PR |= lines;
}

#endif // HW_EXTI_H_