// SPDX-License-Identifier: MIT
// Copyright (c) 2024 Lars Görner

#ifndef HW_GPIO_H_
#define HW_GPIO_H_

#include "../utils/utils.h"

struct gpio {
        volatile unsigned MODER;
        volatile unsigned OTYPER;
        volatile unsigned OSPEEDR;
        volatile unsigned PUPDR;
        volatile unsigned IDR;
        volatile unsigned ODR;
        volatile unsigned BSRR;
        volatile unsigned LCKR;
        volatile unsigned AFRL;
        volatile unsigned AFRH;
        volatile unsigned BRR;
};
#define GPIOA   ((struct gpio *)0x48000000)
#define GPIOB   ((struct gpio *)0x48000400)
#define GPIOC   ((struct gpio *)0x48000800)
#define GPIOD   ((struct gpio *)0x48000C00)
#define GPIOF   ((struct gpio *)0x48001400)

enum gpio_pin {
        GPIO_PIN_0 = BIT(0),
        GPIO_PIN_1 = BIT(1),
        GPIO_PIN_2 = BIT(2),
        GPIO_PIN_3 = BIT(3),
        GPIO_PIN_4 = BIT(4),
        GPIO_PIN_5 = BIT(5),
        GPIO_PIN_6 = BIT(6),
        GPIO_PIN_7 = BIT(7),
        GPIO_PIN_8 = BIT(8),
        GPIO_PIN_9 = BIT(9),
        GPIO_PIN_10 = BIT(10),
        GPIO_PIN_11 = BIT(11),
        GPIO_PIN_12 = BIT(12),
        GPIO_PIN_13 = BIT(13),
        GPIO_PIN_14 = BIT(14),
        GPIO_PIN_15 = BIT(15)
};

//-------------------------------| GPIO_MODER |-------------------------------//

enum gpio_mode {
        GPIO_MODE_INPUT,
        GPIO_MODE_OUTPUT,
        GPIO_MODE_ALTF,
        GPIO_MODE_ANALOG
};

struct gpio_mode_init {
        union {
                struct {
                        enum gpio_mode mode0    : 2;
                        enum gpio_mode mode1    : 2;
                        enum gpio_mode mode2    : 2;
                        enum gpio_mode mode3    : 2;
                        enum gpio_mode mode4    : 2;
                        enum gpio_mode mode5    : 2;
                        enum gpio_mode mode6    : 2;
                        enum gpio_mode mode7    : 2;
                        enum gpio_mode mode8    : 2;
                        enum gpio_mode mode9    : 2;
                        enum gpio_mode mode10   : 2;
                        enum gpio_mode mode11   : 2;
                        enum gpio_mode mode12   : 2;
                        enum gpio_mode mode13   : 2;
                        enum gpio_mode mode14   : 2;
                        enum gpio_mode mode15   : 2;
                };
                unsigned reg_val;
        };
};

static inline void gpio_init_mode(struct gpio * port, struct gpio_mode_init init)
{
        port->MODER = init.reg_val;
}

//------------------------------| GPIO_OTYPER |-------------------------------//

enum gpio_otype {
        GPIO_OTYPE_PUSH_PULL,
        GPIO_OTYPE_OPEN_DRAIN
};

struct gpio_otype_init {
        union {
                struct {
                        enum gpio_otype ot0     : 1;
                        enum gpio_otype ot1     : 1;
                        enum gpio_otype ot2     : 1;
                        enum gpio_otype ot3     : 1;
                        enum gpio_otype ot4     : 1;
                        enum gpio_otype ot5     : 1;
                        enum gpio_otype ot6     : 1;
                        enum gpio_otype ot7     : 1;
                        enum gpio_otype ot8     : 1;
                        enum gpio_otype ot9     : 1;
                        enum gpio_otype ot10    : 1;
                        enum gpio_otype ot11    : 1;
                        enum gpio_otype ot12    : 1;
                        enum gpio_otype ot13    : 1;
                        enum gpio_otype ot14    : 1;
                        enum gpio_otype ot15    : 1;
                };
                unsigned reg_val;
        };
};

static inline void gpio_init_otype(struct gpio * port, struct gpio_otype_init init)
{
        port->OTYPER = init.reg_val;
}

//------------------------------| GPIO_OSPEEDR |------------------------------//

enum gpio_ospeed {
        GPIO_OSPEED_LOW,
        GPIO_OSPEED_MED,
        GPIO_OSPEED_HI
};

struct gpio_ospeed_init {
        union {
                struct {
                        enum gpio_ospeed ospeed0        : 2;
                        enum gpio_ospeed ospeed1        : 2;
                        enum gpio_ospeed ospeed2        : 2;
                        enum gpio_ospeed ospeed3        : 2;
                        enum gpio_ospeed ospeed4        : 2;
                        enum gpio_ospeed ospeed5        : 2;
                        enum gpio_ospeed ospeed6        : 2;
                        enum gpio_ospeed ospeed7        : 2;
                        enum gpio_ospeed ospeed8        : 2;
                        enum gpio_ospeed ospeed9        : 2;
                        enum gpio_ospeed ospeed10       : 2;
                        enum gpio_ospeed ospeed11       : 2;
                        enum gpio_ospeed ospeed12       : 2;
                        enum gpio_ospeed ospeed13       : 2;
                        enum gpio_ospeed ospeed14       : 2;
                        enum gpio_ospeed ospeed15       : 2;
                };
                unsigned reg_val;
        };
};

static inline void gpio_init_ospeed(struct gpio * port, struct gpio_ospeed_init init)
{
        port->OSPEEDR = init.reg_val;
}

//-------------------------------| GPIO_PUPDR |-------------------------------//

enum gpio_pupd {
        GPIO_PUPD_NONE,
        GPIO_PUPD_PULL_UP,
        GPIO_PUPD_PULL_DOWN
};

struct gpio_pupd_init {
        union {
                struct {
                        enum gpio_pupd pupd0    : 2;
                        enum gpio_pupd pupd1    : 2;
                        enum gpio_pupd pupd2    : 2;
                        enum gpio_pupd pupd3    : 2;
                        enum gpio_pupd pupd4    : 2;
                        enum gpio_pupd pupd5    : 2;
                        enum gpio_pupd pupd6    : 2;
                        enum gpio_pupd pupd7    : 2;
                        enum gpio_pupd pupd8    : 2;
                        enum gpio_pupd pupd9    : 2;
                        enum gpio_pupd pupd10   : 2;
                        enum gpio_pupd pupd11   : 2;
                        enum gpio_pupd pupd12   : 2;
                        enum gpio_pupd pupd13   : 2;
                        enum gpio_pupd pupd14   : 2;
                        enum gpio_pupd pupd15   : 2;
                };
                unsigned reg_val;
        };
};

static inline void gpio_init_pupd(struct gpio * port, struct gpio_pupd_init init)
{
        port->PUPDR = init.reg_val;
}

//--------------------------------| GPIO_IDR |--------------------------------//

static inline int gpio_get_val(struct gpio * port, enum gpio_pin pin)
{
        return port->IDR & pin;
}

//--------------------------------| GPIO_ODR |--------------------------------//
//--------------------------------| GPIO_BSRR |-------------------------------//

static inline void gpio_set_pin(struct gpio * port, enum gpio_pin pin)
{
        port->BSRR |= pin;
}

//--------------------------------| GPIO_LCKR |-------------------------------//



//-------------------------------| GPIO_AFRL/H |------------------------------//

struct gpio_afrl_init {
        union {
                struct {
                        unsigned af_sel_0       : 4;
                        unsigned af_sel_1       : 4;
                        unsigned af_sel_2       : 4;
                        unsigned af_sel_3       : 4;
                        unsigned af_sel_4       : 4;
                        unsigned af_sel_5       : 4;
                        unsigned af_sel_6       : 4;
                        unsigned af_sel_7       : 4;
                };
                unsigned reg_val;
        };
};

struct gpio_afrh_init {
        union {
                struct {
                        unsigned af_sel_8       : 4;
                        unsigned af_sel_9       : 4;
                        unsigned af_sel_10      : 4;
                        unsigned af_sel_11      : 4;
                        unsigned af_sel_12      : 4;
                        unsigned af_sel_13      : 4;
                        unsigned af_sel_14      : 4;
                        unsigned af_sel_15      : 4;
                };
                unsigned reg_val;
        };
};

static inline void gpio_init_afr(struct gpio * port, struct gpio_afrl_init initl,
                                 struct gpio_afrh_init inith)
{
        port->AFRL = initl.reg_val;
        port->AFRH = inith.reg_val;
}

//--------------------------------| GPIO_BRR |--------------------------------//

static inline void gpio_clr_pin(struct gpio * port, enum gpio_pin pin)
{
        port->BRR |= pin;
}

#endif // HW_GPIO_H_