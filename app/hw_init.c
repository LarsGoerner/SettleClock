/* SPDX-License-Identifier: MIT */
/* Copyright (c) Lars Görner */

#include "hw_init.h"
#include "../hw/pwr.h"
#include "../hw/rcc.h"
#include "../hw/gpio.h"
#include "../hw/spi.h"
#include "../hw/syscfg.h"
#include "../hw/rtc.h"

static void pwr_init(void)
{
        
}

static void rcc_init(void)
{
        // enable LSI
        rcc_enable_lsi();
        while (!rcc_is_ready_lsi());

        // enable periphery
        rcc_enable_ahb_periphery(RCC_AHB_SRAM | RCC_AHB_GPIOA);
        rcc_enable_apb1_periphery(RCC_APB1_PWR);
        rcc_enable_apb2_periphery(RCC_APB2_SYSCFG | RCC_APB2_SPI1);
}

static void pin_init(void)
{
        // GPIO A
        gpio_init_mode(GPIOA, (struct gpio_mode_init) {
                .mode0 = GPIO_MODE_INPUT, // KEY RIGHT
                .mode1 = GPIO_MODE_INPUT, // KEY DOWN
                .mode2 = GPIO_MODE_INPUT, // KEY LEFT
                .mode3 = GPIO_MODE_INPUT, // KEY UP
                .mode4 = GPIO_MODE_OUTPUT, // SPI1 CS
                .mode5 = GPIO_MODE_ALTF, // SPI1 SCK
                .mode6 = GPIO_MODE_OUTPUT, // DSP DC
                .mode7 = GPIO_MODE_ALTF, // SPI1 MOSI
                .mode8 = GPIO_MODE_ANALOG,
                .mode9 = GPIO_MODE_INPUT, // DSP BUSY
                .mode10 = GPIO_MODE_OUTPUT, // DSP RESET
                .mode11 = GPIO_MODE_ANALOG,
                .mode12 = GPIO_MODE_ANALOG,
                .mode13 = GPIO_MODE_ALTF, // SWDIO
                .mode14 = GPIO_MODE_ALTF, // SWCLK
                .mode15 = GPIO_MODE_ANALOG
        });
        gpio_init_ospeed(GPIOA, (struct gpio_ospeed_init) {
                .ospeed4 = GPIO_OSPEED_HI, // DSP CS
                .ospeed10 = GPIO_OSPEED_HI, // DSP RESET
        });
        gpio_init_pupd(GPIOA, (struct gpio_pupd_init) {
                .pupd0 = GPIO_PUPD_PULL_UP, // KEY RIGHT
                .pupd1 = GPIO_PUPD_PULL_UP, // KEY DOWN
                .pupd2 = GPIO_PUPD_PULL_UP, // KEY LEFT
                .pupd3 = GPIO_PUPD_PULL_UP, // KEY UP
                .pupd4 = GPIO_PUPD_NONE, // SPI1 CS
                .pupd5 = GPIO_PUPD_NONE, // SPI1 SCK
                .pupd6 = GPIO_PUPD_NONE, // DSP DC
                .pupd7 = GPIO_PUPD_NONE, // SPI1 MOSI
                .pupd8 = GPIO_PUPD_PULL_DOWN,
                .pupd9 = GPIO_PUPD_NONE, // DSP BUSY
                .pupd10 = GPIO_PUPD_NONE, // DSP RESET
                .pupd11 = GPIO_PUPD_PULL_DOWN,
                .pupd12 = GPIO_PUPD_PULL_DOWN,
                .pupd13 = GPIO_PUPD_NONE, // SWDIO
                .pupd14 = GPIO_PUPD_NONE, // SWCLK
                .pupd15 = GPIO_PUPD_PULL_DOWN
        });
}

static void dsp_spi_init(void)
{
        spi_init_cr1(SPI1, (struct spi_cr1_init) {
                .br = SPI_BR_DIV_4,
                .cpol = 0,
                .cpha = 0,
                .ssm = 0,
                .ssi = 0,
                .mstr = 1
        });
        spi_init_cr2(SPI1, (struct spi_cr2_init) {
                .ss_oe = 1,
                .frf = SPI_FRF_MOTOROLA,
                .ds = 8 - 1,
                .frx_th = SPI_FRXTH_8
        });
}

static void syscfg_init(void)
{
        syscfg_init_cfg((struct syscfg_cfgr1) { 0 }, (struct syscfg_cfgr2) { 0 });
        syscfg_init_exti((struct syscfg_exti_init_1) { 0 },
                         (struct syscfg_exti_init_2) { 0 },
                         (struct syscfg_exti_init_3) { 0 },
                         (struct syscfg_exti_init_4) { 0 });
}

static void rtc_init(void)
{
        pwr_disable_bdp();
        rcc_bd_set_rtc_sel(RCC_RTCSEL_LSI);
        rcc_bd_enable_rtc();
        rtc_unlock_write_protection();
}

void hw_init(void)
{
        rcc_init();
        pwr_init();
        pin_init();
        dsp_spi_init();
        syscfg_init();
        rtc_init();
}