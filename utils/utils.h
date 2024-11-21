// SPDX-License-Identifier: MIT
// Copyright (c) 2024 Lars Görner

#ifndef UTILS_UTILS_H_
#define UTILS_UTILS_H_

// Attributes
#define __noreturn      __attribute__((noreturn))
#define __naked         __attribute__((naked))
#define __isr           __attribute__((interrupt("IRQ")))
#define __nvic __attribute__((weak, alias("nvic_default_handler")))

// Special ASM commands
#define __NOP()         __asm__("nop")
#define __SEV()         __asm__("sev")
#define __WFE()         __asm__("wfe")
#define __WFI()         __asm__("wfi")

// General
#define BIT(n)          (1U << (n))
#define ARRAY_SIZE(a)   (sizeof(a) / sizeof(a[0]))

// Memory Macros
#define KB(n)           (n * 1024)
#define MB(n)           (KB(n) * 1024)

// Frequency Macros
#define KHz(n)          (n * 1000)
#define MHz(n)          (KHz(n) * 1000)

#endif // UTILS_UTILS_H_