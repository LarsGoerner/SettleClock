/* SPDX-License-Identifier: MIT */
/* Copyright (c) Lars Görner */

#include "../utils/utils.h"

extern int _sdata, _edata;
extern const int _sidata;
extern int _sbss, _ebss;
extern int _estack;
extern void __noreturn main(void);

void __isr nvic_default_handler(void)
{
        while (1);
}

void __isr nvic_reset_handler(void)
{
        int * ram_ptr;
        const int * rom_ptr;
        unsigned int cpy_len;

        // .data
        ram_ptr = &_sdata;
        rom_ptr = &_sidata;
        cpy_len = &_edata - &_sdata;

        while (cpy_len--) {
                *ram_ptr++ = *rom_ptr++;
        }

        // .bss
        ram_ptr = &_sbss;
        cpy_len = &_ebss - &_sbss;

        while (cpy_len--) {
                *ram_ptr++ = 0;
        }

        // call main
        main();
}

typedef void (*nvic_fun)(void);

void nvic_nmi_handler(void) __isr __nvic;
void nvic_hard_fault_handler(void) __isr __nvic;
void nvic_sv_call_handler(void) __isr __nvic;
void nvic_pend_sv_handler(void) __isr __nvic;
void nvic_systick_handler(void) __isr __nvic;

void nvic_wwdg_handler(void) __isr __nvic;
void nvic_rtc_handler(void) __isr __nvic;
void nvic_flash_handler(void) __isr __nvic;
void nvic_rcc_handler(void) __isr __nvic;
void nvic_exti0_1_handler(void) __isr __nvic;
void nvic_exti2_3_handler(void) __isr __nvic;
void nvic_exti4_15_handler(void) __isr __nvic;
void nvic_dma_ch1_handler(void) __isr __nvic;
void nvic_dma_ch2_3_handler(void) __isr __nvic;
void nvic_dma_ch4_5_handler(void) __isr __nvic;
void nvic_adc_handler(void) __isr __nvic;
void nvic_tim1_brk_up_trg_com_handler(void) __isr __nvic;
void nvic_tim1_cc_handler(void) __isr __nvic;
void nvic_tim3_handler(void) __isr __nvic;
void nvic_tim6_handler(void) __isr __nvic;
void nvic_tim14_handler(void) __isr __nvic;
void nvic_tim15_handler(void) __isr __nvic;
void nvic_tim16_handler(void) __isr __nvic;
void nvic_tim17_handler(void) __isr __nvic;
void nvic_i2c1_handler(void) __isr __nvic;
void nvic_i2c2_handler(void) __isr __nvic;
void nvic_spi1_handler(void) __isr __nvic;
void nvic_spi2_handler(void) __isr __nvic;
void nvic_usart1_handler(void) __isr __nvic;
void nvic_usart2_handler(void) __isr __nvic;
void nvic_usart3_4_5_6_handler(void) __isr __nvic;
void nvic_usb_handler(void) __isr __nvic;

const nvic_fun VEC_TBL[] __attribute__((section(".vector_table"))) = {
        (nvic_fun)&_estack,
        &nvic_reset_handler,
        &nvic_nmi_handler,
        &nvic_hard_fault_handler,
        // 8 elements space
        0, 0, 0, 0, 0, 0, 0,
        &nvic_sv_call_handler,
        // 3 elements space
        0, 0,
        &nvic_pend_sv_handler,
        &nvic_systick_handler,
        /* --- */
        &nvic_wwdg_handler,
        0,
        &nvic_rtc_handler,
        &nvic_flash_handler,
        &nvic_rcc_handler,
        &nvic_exti0_1_handler,
        &nvic_exti2_3_handler,
        &nvic_exti4_15_handler,
        0,
        &nvic_dma_ch1_handler,
        &nvic_dma_ch2_3_handler,
        &nvic_dma_ch4_5_handler,
        &nvic_adc_handler,
        &nvic_tim1_brk_up_trg_com_handler,
        &nvic_tim1_cc_handler,
        0,
        &nvic_tim3_handler,
        &nvic_tim6_handler,
        0,
        &nvic_tim14_handler,
        &nvic_tim15_handler,
        &nvic_tim16_handler,
        &nvic_tim17_handler,
        &nvic_i2c1_handler,
        &nvic_i2c2_handler,
        &nvic_spi1_handler,
        &nvic_spi2_handler,
        &nvic_usart1_handler,
        &nvic_usart2_handler,
        &nvic_usart3_4_5_6_handler,
        0,
        &nvic_usb_handler
};