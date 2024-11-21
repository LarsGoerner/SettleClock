/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2024 Lars Görner */

#ifndef HW_RCC_H_
#define HW_RCC_H_

#include "../utils/utils.h"

struct rcc {
        volatile unsigned CR;
        volatile unsigned CFGR;
        volatile unsigned CIR;
        volatile unsigned APB2RSTR;
        volatile unsigned APB1RSTR;
        volatile unsigned AHBENR;
        volatile unsigned APB2ENR;
        volatile unsigned APB1ENR;
        volatile unsigned BDCR;
        volatile unsigned CSR;
        volatile unsigned AHBRSTR;
        volatile unsigned CFGR2;
        volatile unsigned CFGR3;
        volatile unsigned CR2;
};
#define RCC     ((struct rcc *)0x40021000)

enum rcc_ahb_peri {
        RCC_AHB_DMA     = BIT(0),
        RCC_AHB_SRAM    = BIT(2),
        RCC_AHB_FLITF   = BIT(4),
        RCC_AHB_CRC     = BIT(6),
        RCC_AHB_GPIOA   = BIT(17),
        RCC_AHB_GPIOB   = BIT(18),
        RCC_AHB_GPIOC   = BIT(19),
        RCC_AHB_GPIOD   = BIT(20),
        RCC_AHB_GPIOF   = BIT(22)
};

enum rcc_apb1_peri {
        RCC_APB1_TIM3   = BIT(1),
        RCC_APB1_TIM6   = BIT(4),
        RCC_APB1_TIM7   = BIT(5),
        RCC_APB1_TIM14  = BIT(8),
        RCC_APB1_WWDG   = BIT(11),
        RCC_APB1_SPI2   = BIT(14),
        RCC_APB1_USART2 = BIT(17),
        RCC_APB1_USART3 = BIT(18),
        RCC_APB1_USART4 = BIT(19),
        RCC_APB1_USART5 = BIT(20),
        RCC_APB1_I2C1   = BIT(21),
        RCC_APB1_I2C2   = BIT(22),
        RCC_APB1_USB    = BIT(23),
        RCC_APB1_PWR    = BIT(28)
};

enum rcc_apb2_peri {
        RCC_APB2_SYSCFG = BIT(0),
        RCC_APB2_USART6 = BIT(5),
        RCC_APB2_ADC    = BIT(9),
        RCC_APB2_TIM1   = BIT(11),
        RCC_APB2_SPI1   = BIT(12),
        RCC_APB2_USART1 = BIT(14),
        RCC_APB2_TIM15  = BIT(16),
        RCC_APB2_TIM16  = BIT(17),
        RCC_APB2_TIM17  = BIT(18),
        RCC_APB2_DBGMCU = BIT(22)
};

//---------------------------------| RCC_CR |---------------------------------//

struct rcc_cr {
        unsigned hsi_on         : 1;
        unsigned hsi_rdy        : 1;
        unsigned                : 1;
        unsigned hsi_trim       : 5;
        
        unsigned hsi_cal        : 8;

        unsigned hse_on         : 1;
        unsigned hse_rdy        : 1;
        unsigned hse_byp        : 1;
        unsigned css_on         : 1;
        unsigned                : 4;

        unsigned pll_on         : 1;
        unsigned pll_rdy        : 1;
        unsigned                : 6;
};

static inline void rcc_enable_hsi(void)
{
        RCC->CR |= BIT(0);
}

static inline void rcc_disable_hsi(void)
{
        RCC->CR &= ~BIT(0);
}

static inline int rcc_is_ready_hsi(void)
{
        return RCC->CR & BIT(1);
}

static inline void rcc_enable_hse(void)
{
        RCC->CR |= BIT(16);
}

static inline void rcc_disable_hse(void)
{
        RCC->CR &= ~BIT(16);
}

static inline int rcc_is_ready_hse(void)
{
        return RCC->CR & BIT(17);
}

static inline void rcc_bypass_hse(void)
{
        RCC->CR |= BIT(18);
}

static inline void rcc_enable_css(void)
{
        RCC->CR |= BIT(19);
}

static inline void rcc_enable_pll(void)
{
        RCC->CR |= BIT(24);
}

static inline void rcc_disable_pll(void)
{
        RCC->CR &= ~BIT(24);
}

static inline int rcc_is_ready_pll(void)
{
        return RCC->CR & BIT(25);
}

//--------------------------------| RCC_CFGR |--------------------------------//

enum rcc_mco_pre {
        RCC_MCO_PRE_1,
        RCC_MCO_PRE_2,
        RCC_MCO_PRE_4,
        RCC_MCO_PRE_8,
        RCC_MCO_PRE_16,
        RCC_MCO_PRE_32,
        RCC_MCO_PRE_64,
        RCC_MCO_PRE_128
};

enum rcc_mco {
        RCC_MCO_DIS,
        RCC_MCO_HSI14,
        RCC_MCO_LSI,
        RCC_MCO_LSE,
        RCC_MCO_SYSCLK,
        RCC_MCO_HSI,
        RCC_MCO_HSE,
        RCC_MCO_PLL
};

enum rcc_pll_mul {
        RCC_PLL_MUL_2,
        RCC_PLL_MUL_3,
        RCC_PLL_MUL_4,
        RCC_PLL_MUL_5,
        RCC_PLL_MUL_6,
        RCC_PLL_MUL_7,
        RCC_PLL_MUL_8,
        RCC_PLL_MUL_9,
        RCC_PLL_MUL_10,
        RCC_PLL_MUL_11,
        RCC_PLL_MUL_12,
        RCC_PLL_MUL_13,
        RCC_PLL_MUL_14,
        RCC_PLL_MUL_15,
        RCC_PLL_MUL_16
};

enum rcc_pll_src {
        RCC_PLL_SRC_HSI_DIV_2,
        RCC_PLL_SRC_HSI,
        RCC_PLL_SRC_HSE
};

enum rcc_ppre {
        RCC_PPRE_1,
        RCC_PPRE_2 = 4,
        RCC_PPRE_4,
        RCC_PPRE_8,
        RCC_PPRE_16
};

enum rcc_hpre {
        RCC_HPRE_1,
        RCC_HPRE_2 = 8,
        RCC_HPRE_4,
        RCC_HPRE_8,
        RCC_HPRE_16,
        RCC_HPRE_64,
        RCC_HPRE_128,
        RCC_HPRE_256,
        RCC_HPRE_512
};

enum rcc_sw {
        RCC_SW_HSI,
        RCC_SW_HSE,
        RCC_SW_PLL
};

struct rcc_cfg_init {
        union {
                struct {
                        enum rcc_sw sw                  : 2;
                        enum rcc_sw sws                 : 2;
                        enum rcc_hpre hpre              : 4;

                        enum rcc_ppre ppre              : 3;
                        unsigned                        : 3;
                        unsigned adc_pre                : 1;
                        enum rcc_pll_src pll_src        : 2;
                        unsigned pllxt_pre              : 1;
                        enum rcc_pll_mul pll_mul        : 4;
                        unsigned                        : 2;

                        enum rcc_mco mco                : 4;
                        enum rcc_mco_pre mco_pre        : 3;
                        unsigned pll_no_div             : 1;
                };
                unsigned reg_val;
        };
};

static inline void rcc_init_cfg1(struct rcc_cfg_init init)
{
        RCC->CFGR = init.reg_val;
}

//---------------------------------| RCC_CIR |--------------------------------//



//------------------------------| RCC_APB2RSTR |------------------------------//

static inline void rcc_reset_apb2_periphery(enum rcc_apb2_peri p)
{
        RCC->APB2RSTR = (unsigned)p;
}

//------------------------------| RCC_APB1RSTR |------------------------------//

static inline void rcc_reset_apb1_periphery(enum rcc_apb1_peri p)
{
        RCC->APB1RSTR = (unsigned)p;
}

//-------------------------------| RCC_AHBENR |-------------------------------//

static inline void rcc_enable_ahb_periphery(enum rcc_ahb_peri p)
{
        RCC->AHBENR = (unsigned)p;
}

//------------------------------| RCC_APB2ENR |-------------------------------//

static inline void rcc_enable_apb2_periphery(enum rcc_apb2_peri p)
{
        RCC->APB2ENR = (unsigned)p;
}

//------------------------------| RCC_APB1ENR |-------------------------------//

static inline void rcc_enable_apb1_periphery(enum rcc_apb1_peri p)
{
        RCC->APB1ENR = (unsigned)p;
}

//--------------------------------| RCC_BDCR |--------------------------------//

enum rcc_rtcsel {
        RCC_RTCSEL_NONE,
        RCC_RTCSEL_LSE,
        RCC_RTCSEL_LSI,
        RCC_RTCSEL_LSE_DIV32
};

static inline void rcc_bd_set_rtc_sel(enum rcc_rtcsel sel)
{
        RCC->BDCR &= ~(3 << 8);
        RCC->BDCR |= (sel & 3) << 8;
}

static inline void rcc_bd_enable_rtc(void)
{
        RCC->BDCR |= BIT(15);
}

static inline void rcc_bd_disable_rtc(void)
{
        RCC->BDCR &= ~BIT(15);
}

//---------------------------------| RCC_CSR |--------------------------------//

static inline void rcc_enable_lsi(void)
{
        RCC->CSR |= BIT(0);
}

static inline void rcc_disable_lsi(void)
{
        RCC->CSR &= ~BIT(0);
}

static inline int rcc_is_ready_lsi(void)
{
        return RCC->CSR & BIT(1);
}

//-------------------------------| RCC_AHBRSTR |------------------------------//

static inline void rcc_reset_ahb_periphery(enum rcc_ahb_peri p)
{
        RCC->AHBENR = (unsigned)p;
}

//--------------------------------| RCC_CFGR2 |-------------------------------//

struct rcc_cfgr2 {
        unsigned pre_div        : 4;
        unsigned                : 4;

        unsigned                : 24;
};

static inline void rcc_set_pre_div(unsigned pre_div)
{
        RCC->CFGR2 = (pre_div - 1) & 0xFF;
}

//--------------------------------| RCC_CFGR3 |-------------------------------//

enum rcc_usb_sw {
        RCC_USB_SW_DIS,
        RCC_USB_SW_PLL
};

enum rcc_i2c1_sw {
        RCC_I2C1_SW_HSI,
        RCC_I2C1_SW_SYSCLK
};

enum rcc_usart1_sw {
        RCC_USART1_SW_PCLK,
        RCC_USART1_SW_SYSCLK,
        RCC_USART1_SW_LSE,
        RCC_USART1_SW_HSI
};

static inline void rcc_set_usb_sw(enum rcc_usb_sw sw)
{
        RCC->CFGR3 &= ~BIT(8);
        RCC->CFGR3 |= (sw & 1) << 8;
}

static inline void rcc_set_i2c1_sw(enum rcc_i2c1_sw sw)
{
        RCC->CFGR3 &= ~BIT(4);
        RCC->CFGR3 |= (sw & 1) << 4;
}

static inline void rcc_set_usart1_sw(enum rcc_usart1_sw sw)
{
        RCC->CFGR3 &= ~0x3;
        RCC->CFGR3 |= sw & 0x3;
}

//--------------------------------| RCC_CR2 |---------------------------------//

static inline void rcc_enable_hsi14(void)
{
        RCC->CR2 |= BIT(0);
}

static inline void rcc_disable_hsi14(void)
{
        RCC->CR2 &= ~BIT(0);
}

static inline int rcc_is_ready_hsi14(void)
{
        return RCC->CR2 & BIT(1);
}

#endif // HW_RCC_H_