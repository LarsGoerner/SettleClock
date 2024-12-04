/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2024 Lars Görner */

#ifndef HW_SCB_H_
#define HW_SCB_H_

#include "../utils/utils.h"

struct scb {
        volatile unsigned CPUID;
        volatile unsigned ICS;
        unsigned reserved1;
        volatile unsigned AIRC;
        volatile unsigned SC;
        volatile unsigned CC;
        unsigned reserved2;
        volatile unsigned SHP2;
        volatile unsigned SHP3;
};
#define SCB    ((struct scb *)0xE000ED00) 

//---| CPUID base register

//---| Interrupt control and state register

//---| Application interrupt and reset control register

//---| System control register

enum scb_sleep_mode {
        SCB_SLEEP,
        SCB_DEEP_SLEEP
};

static inline void scb_set_sleep_mode(enum scb_sleep_mode mode)
{
        if (mode) {
                SCB->SC |= BIT(2);
        }
        else {
                SCB->SC &= ~BIT(2);
        }
}

//---| Configuration and control register

//---| System handler priority registers



#endif // HW_SCB_H_