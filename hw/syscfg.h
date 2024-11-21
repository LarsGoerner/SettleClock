/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2024 Lars Görner */

#ifndef HW_SYSCFG_H_
#define HW_SYSCFG_H_

struct syscfg {
        volatile unsigned CFGR1;
        volatile unsigned EXTICR1;
        volatile unsigned EXTICR2;
        volatile unsigned EXTICR3;
        volatile unsigned EXTICR4;
        volatile unsigned CFGR2;
};
#define SYSCFG          ((struct syscfg *)0x40010000)

//---| SYSCFG configuration register 1 & 2

enum syscfg_mem_mode {
        SYSCFG_MEM_MAIN_MEM,
        SYSCFG_MEM_SYS_FLASH,
        SYSCFG_MEM_EMBED_SRAM,
};

struct syscfg_cfgr1 {
        union {
                struct {
                        enum syscfg_mem_mode mem_mode   : 2;
                        unsigned                        : 2;
                        unsigned pa11_pa12_rmp          : 1;
                        unsigned                        : 3;

                        unsigned adc_dma_rmp            : 1;
                        unsigned usart1_tx_dma_rmp      : 1;
                        unsigned usart1_rx_dma_rmp      : 1;
                        unsigned tim16_dma_rmp          : 1;
                        unsigned tim17_dma_rmp          : 1;
                        unsigned                        : 3;

                        unsigned i2c_pb6_fmp            : 1;
                        unsigned i2c_pb7_fmp            : 1;
                        unsigned i2c_pb8_fmp            : 1;
                        unsigned i2c_pb9_fmp            : 1;
                        unsigned i2c1_fmp               : 1;
                        unsigned i2c2_fmp               : 1;
                        unsigned i2c_pa9_fmp            : 1;
                        unsigned i2c_pa10_fmp           : 1;

                        unsigned                        : 2;
                        unsigned usart3_dma_rmp         : 1;
                };
                unsigned reg_val;
        };
};

struct syscfg_cfgr2
{
        union {
                struct {
                        unsigned lockup_lock            : 1;
                        unsigned sram_parity_lock       : 1;
                        unsigned                        : 6;

                        unsigned sram_pef               : 1;
                };
                unsigned reg_val;
        };
};


static inline void syscfg_init_cfg(struct syscfg_cfgr1 cfg1, struct syscfg_cfgr2 cfg2)
{
        SYSCFG->CFGR1 = cfg1.reg_val;
        SYSCFG->CFGR2 = cfg2.reg_val;
}

//---| SYSCFG external interrupt configuration register 1 - 4

enum syscfg_exti {
        SYSCFG_EXTI_PA,
        SYSCFG_EXTI_PB,
        SYSCFG_EXTI_PC,
        SYSCFG_EXTI_PD,
        SYSCFG_EXTI_PF = 5,
};

struct syscfg_exti_init_1 {
        union {
                struct {
                        enum syscfg_exti exti0  : 4;
                        enum syscfg_exti exti1  : 4;
                        enum syscfg_exti exti2  : 4;
                        enum syscfg_exti exti3  : 4;
                };
                unsigned reg_val;
        };
};
struct syscfg_exti_init_2 {
        union {
                struct {
                        enum syscfg_exti exti4  : 4;
                        enum syscfg_exti exti5  : 4;
                        enum syscfg_exti exti6  : 4;
                        enum syscfg_exti exti7  : 4;
                };
                unsigned reg_val;
        };
};

struct syscfg_exti_init_3 {
        union {
                struct {
                        enum syscfg_exti exti8  : 4;
                        enum syscfg_exti exti9  : 4;
                        enum syscfg_exti exti10 : 4;
                        enum syscfg_exti exti11 : 4;
                };
                unsigned reg_val;
        };
};

struct syscfg_exti_init_4 {
        union {
                struct {
                        enum syscfg_exti exti12 : 4;
                        enum syscfg_exti exti13 : 4;
                        enum syscfg_exti exti14 : 4;
                        enum syscfg_exti exti15 : 4;
                };
                unsigned reg_val;
        };
};

static inline void syscfg_init_exti(struct syscfg_exti_init_1 init1,
                                    struct syscfg_exti_init_2 init2,
                                    struct syscfg_exti_init_3 init3,
                                    struct syscfg_exti_init_4 init4)
{
        SYSCFG->EXTICR1 = init1.reg_val;
        SYSCFG->EXTICR2 = init2.reg_val;
        SYSCFG->EXTICR3 = init3.reg_val;
        SYSCFG->EXTICR4 = init4.reg_val;
}

#endif // HW_SYSCFG_H_