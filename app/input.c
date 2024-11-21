/* SPDX-License-Identifier: MIT */
/* Copyright (c) Lars Görner */

#include "input.h"
#include "../utils/utils.h"
#include "../hw/gpio.h"
#include "../hw/exti.h"
#include "../hw/nvic.h"

struct input_pin pending_inputs = { 0 };

#define RIGHT_EXTI      EXTI_LINE_0
#define DOWN_EXTI       EXTI_LINE_1
#define LEFT_EXTI       EXTI_LINE_2
#define UP_EXTI         EXTI_LINE_3
#define ALL_EXTI        LEFT_EXTI | RIGHT_EXTI | UP_EXTI | DOWN_EXTI

void input_init(void)
{
        exti_enable_falling_trigger_event(ALL_EXTI);
}

void input_enable(void)
{
        exti_enable_line_interrupt(ALL_EXTI);
        nvic_enable_interrupt(NVIC_IR_5 | NVIC_IR_6);
}

void input_disable(void)
{
        exti_disable_line_interrupt(ALL_EXTI);
        nvic_enable_interrupt(NVIC_IR_5 | NVIC_IR_6);
}

void input_ack_inputs(void)
{
        pending_inputs = (struct input_pin){ 0 };
}

static inline void input_get_pending_io_irqs(void)
{
        register int pends = exti_pending(ALL_EXTI);
        if (pends & UP_EXTI) {
                pending_inputs.up_key = 1;
        } else if (pends & DOWN_EXTI) {
                pending_inputs.down_key = 1;
        } else if (pends & LEFT_EXTI) {
                pending_inputs.left_key = 1;
        } else if (pends & RIGHT_EXTI) {
                pending_inputs.right_key = 1;
        }
        exti_ack_pending(ALL_EXTI);
}

void __isr nvic_exti0_1_handler(void)
{
        input_get_pending_io_irqs();
        nvic_clear_pending_interrupt(NVIC_IR_5);
}

void __isr nvic_exti2_3_handler(void)
{
        input_get_pending_io_irqs();
        nvic_clear_pending_interrupt(NVIC_IR_6);
}
