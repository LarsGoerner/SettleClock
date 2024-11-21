/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2024 Lars Görner */

#ifndef HW_I2C_H_
#define HW_I2C_H_

#include "../utils/utils.h"

struct i2c {
        volatile unsigned CR1;
        volatile unsigned CR2;
        volatile unsigned OAR1;
        volatile unsigned OAR2;
        volatile unsigned TIMINGR;
        volatile unsigned TIMEOUTR;
        volatile unsigned ISR;
        volatile unsigned ICR;
        volatile unsigned PECR;
        volatile unsigned RXDR;
        volatile unsigned TXDR;
};
#define I2C1    ((struct i2c *)0x40005400)
#define I2C2    ((struct i2c *)0x40005800)

//--------------------------------| I2C_CR1 |---------------------------------//

static inline void i2c_enable_periphery(struct i2c * i2c)
{
        i2c->CR1 |= BIT(0);
}

static inline void i2c_disable_periphery(struct i2c * i2c)
{
        i2c->CR1 &= ~BIT(0);
}

static inline void i2c_enable_txie(struct i2c * i2c)
{
        i2c->CR1 |= BIT(1);
}

static inline void i2c_disable_txie(struct i2c * i2c)
{
        i2c->CR1 &= ~BIT(1);
}

static inline void i2c_enable_rxie(struct i2c * i2c)
{
        i2c->CR1 |= BIT(2);
}

static inline void i2c_disable_rxie(struct i2c * i2c)
{
        i2c->CR1 &= ~BIT(2);
}

//--------------------------------| I2C_CR2 |---------------------------------//

enum i2c_rd_wrn {
        I2C_RD_WRN_WRITE,
        I2C_RD_WRN_READ
};

enum i2c_add10 {
        I2C_ADD10_7BIT,
        I2C_ADD10_10BIT
};

static inline void i2c_set_rd_wrn(struct i2c * i2c, enum i2c_rd_wrn rd_wrn)
{
        i2c->CR2 &= ~BIT(10);
        i2c->CR2 |= (rd_wrn & 1) << 10;
}

static inline void i2c_set_add10(struct i2c * i2c, enum i2c_add10 add10)
{
        i2c->CR2 &= ~BIT(11);
        i2c->CR2 |= (add10 & 1) << 11;
}

static inline void i2c_set_slave_addr(struct i2c * i2c, unsigned char addr)
{
        i2c->CR2 &= ~(0x7F << 1);
        i2c->CR2 |= (addr & 0x7F) << 1;
}

static inline void i2c_set_nbytes(struct i2c * i2c, unsigned char nb)
{
        i2c->CR2 &= ~(0xFF << 16);
        i2c->CR2 |= (nb & 0xFF) << 16;
}

static inline void i2c_enable_auto_end(struct i2c * i2c)
{
        i2c->CR2 |= BIT(25);
}

static inline void i2c_start(struct i2c * i2c)
{
        i2c->CR2 |= BIT(13);
}

//--------------------------------| I2C_OAR1 |--------------------------------//



//--------------------------------| I2C_OAR2 |--------------------------------//



//-------------------------------| I2C_TIMING |-------------------------------//

struct i2c_timing_init {
        union {
                struct {
                        unsigned scll           : 8;
                        unsigned schl           : 8;
                        unsigned sda_del        : 4;
                        unsigned scl_del        : 4;
                        unsigned                : 4;
                        unsigned presc          : 4;
                };
                unsigned reg_val;
        };
};

static inline void i2c_init_timing(struct i2c * i2c, struct i2c_timing_init init)
{
        i2c->TIMINGR = init.reg_val;
}

//------------------------------| I2C_TIMEOUTR |------------------------------//

struct i2c_timeout_init {
        union {
                struct {
                        unsigned timeout_a      : 12;
                        unsigned t_idle         : 1;
                        unsigned                : 2;
                        unsigned timeout_en     : 1;
                        unsigned timeout_b      : 12;
                        unsigned                : 3;
                        unsigned text_en        : 1;
                };
                unsigned reg_val;
        };
};

static inline void i2c_init_timeout(struct i2c * i2c, struct i2c_timeout_init init)
{
        i2c->TIMEOUTR = init.reg_val;
}

//--------------------------------| I2C_ISR |---------------------------------//

static inline int i2c_is_ready_tx(struct i2c * i2c)
{
        return i2c->ISR & BIT(1);
}

static inline int i2c_is_ready_rx(struct i2c * i2c)
{
        return i2c->ISR & BIT(2);
}

//--------------------------------| I2C_ICR |---------------------------------//



//--------------------------------| I2C_PECR |--------------------------------//



//--------------------------------| I2C_RXDR |--------------------------------//

static inline unsigned char i2c_read(struct i2c * i2c)
{
        return i2c->RXDR & 0xFF;
}

//--------------------------------| I2C_TXDR |--------------------------------//

static inline void i2c_write(struct i2c * i2c, unsigned char data)
{
        i2c->TXDR = data;
}

#endif // HW_I2C_H_