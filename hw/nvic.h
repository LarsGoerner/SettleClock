/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2024 Lars Görner */

#ifndef HW_NVIC_H_
#define HW_NVIC_H_

#include "../utils/utils.h"

#define NVIC_ISER       ((volatile unsigned *)0xE000E100)
#define NVIC_ICER       ((volatile unsigned *)0xE000E180)
#define NVIC_ISPR       ((volatile unsigned *)0xE000E200)
#define NVIC_ICPR       ((volatile unsigned *)0xE000E280)
#define NVIC_IPR        ((volatile unsigned **)0xE000E400)

#define NVIC_IR_0       BIT(0)
#define NVIC_IR_1       BIT(1)
#define NVIC_IR_2       BIT(2)
#define NVIC_IR_3       BIT(3)
#define NVIC_IR_4       BIT(4)
#define NVIC_IR_5       BIT(5)
#define NVIC_IR_6       BIT(6)
#define NVIC_IR_7       BIT(7)
#define NVIC_IR_8       BIT(8)
#define NVIC_IR_9       BIT(9)
#define NVIC_IR_10      BIT(10)
#define NVIC_IR_11      BIT(11)
#define NVIC_IR_12      BIT(12)
#define NVIC_IR_13      BIT(13)
#define NVIC_IR_14      BIT(14)
#define NVIC_IR_15      BIT(15)
#define NVIC_IR_16      BIT(16)
#define NVIC_IR_17      BIT(17)
#define NVIC_IR_18      BIT(18)
#define NVIC_IR_19      BIT(19)
#define NVIC_IR_20      BIT(20)
#define NVIC_IR_21      BIT(21)
#define NVIC_IR_22      BIT(22)
#define NVIC_IR_23      BIT(23)
#define NVIC_IR_24      BIT(24)
#define NVIC_IR_25      BIT(25)
#define NVIC_IR_26      BIT(26)
#define NVIC_IR_27      BIT(27)
#define NVIC_IR_28      BIT(28)
#define NVIC_IR_29      BIT(29)
#define NVIC_IR_30      BIT(30)
#define NVIC_IR_31      BIT(31)

static inline void nvic_enable_interrupt(unsigned nums)
{
        *NVIC_ISER |= nums;
}

static inline void nvic_disable_interrupt(unsigned nums)
{
        *NVIC_ICER |= nums;
}

static inline void nvic_clear_pending_interrupt(unsigned nums)
{
        *NVIC_ICPR |= nums;
}

static inline int nvic_is_pending_interrupt(unsigned nums)
{
        return *NVIC_ICPR & nums;
}

#endif // HW_NVIC_H_