/* SPDX-License-Identifier: MIT */
/* Copyright (c) Lars Görner */

#ifndef EDIT_INIT_DATE_H_
#define EDIT_INIT_DATE_H_

#include "../hw/rtc.h"

extern struct rtc_date init_date;
extern struct rtc_date end_date;

#define BCD2UINT(tens, units, uint)     \
do {                                    \
        uint = tens * 10 + units;       \
} while (0)

#define UINT2BCD(uint, tens, units)     \
do {                                    \
        register unsigned tmp = uint;   \
        tens = 0;                       \
        while (tmp >= 10) {             \
                tmp -= 10;              \
                ++tens;                 \
        }                               \
        units = tmp;                    \
} while (0)

void enter_init_date_enter_routine(void);

#endif // EDIT_INIT_DATE_H_