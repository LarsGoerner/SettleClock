/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2024 Lars Görner */

#ifndef HW_PWR_H_
#define HW_PWR_H_

#include "../utils/utils.h"

struct pwr {
        volatile unsigned C;
        volatile unsigned CS;
};
#define PWR     ((struct pwr *)0x40007000)

//---------------------------------| PWR_CR |---------------------------------//

static inline void pwr_enable_lpds(void)
{
        PWR->C |= BIT(0);
}

static inline void pwr_disable_lpds(void)
{
        PWR->C &= ~BIT(0);
}

static inline void pwr_enable_pdds(void)
{
        PWR->C |= BIT(1);
}

static inline void pwr_disable_pdds(void)
{
        PWR->C &= ~BIT(1);
}

static inline void pwr_disable_bdp(void)
{
        PWR->C |= BIT(8);
}

static inline void pwr_enable_bdp(void)
{
        PWR->C &= ~BIT(8);
}

//---------------------------------| PWR_CSR |--------------------------------//



#endif // HW_PWR_H_