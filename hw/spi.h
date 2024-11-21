/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2024 Lars Görner */

#ifndef HW_SPI_H_
#define HW_SPI_H_

#include "../utils/utils.h"

/** @brief SPI registers */
struct spi {
        volatile unsigned CR1;
        volatile unsigned CR2;
        volatile unsigned SR;
        volatile unsigned DR;
        volatile unsigned CRPCR;
        volatile unsigned RXCRCR;
        volatile unsigned TXCRCR;
};
#define SPI1    ((struct spi *)0x40013000)
#define SPI2    ((struct spi *)0x40003800)

//--------------------------------| SPI_CR1 |---------------------------------//

enum spi_br {
        SPI_BR_DIV_2,
        SPI_BR_DIV_4,
        SPI_BR_DIV_8,
        SPI_BR_DIV_16,
        SPI_BR_DIV_32,
        SPI_BR_DIV_64,
        SPI_BR_DIV_128,
        SPI_BR_DIV_256
};

enum spi_bidi_mode {
        SPI_BIDI_MODE_2_LINE,
        SPI_BIDI_MODE_1_LINE
};

enum spi_crcl {
        SPI_CRCL_8,
        SPI_CRCL_16
};

struct spi_cr1_init {
        union {
                struct {
                        unsigned cpha                   : 1;
                        unsigned cpol                   : 1;
                        unsigned mstr                   : 1;
                        enum spi_br br                  : 3;
                        unsigned spe                    : 1;
                        unsigned lsb_first              : 1;

                        unsigned ssi                    : 1;
                        unsigned ssm                    : 1;
                        unsigned rx_only                : 1;
                        enum spi_crcl crcl              : 1;
                        unsigned crc_next               : 1;
                        unsigned crc_en                 : 1;
                        unsigned bidi_oe                : 1;
                        enum spi_bidi_mode bidi_mode    : 1;
                };
                unsigned reg_val;
        };
};

static inline void spi_init_cr1(struct spi * dev, struct spi_cr1_init cr1)
{
        dev->CR1 = cr1.reg_val;
}

static inline void spi_set_bidi_mode(struct spi * dev, enum spi_bidi_mode mode)
{
        dev->CR1 &= ~BIT(15);
        dev->CR1 |= (mode & 1) << 15;
}

static inline void spi_enable(struct spi * dev)
{
        dev->CR1 |= BIT(6);
}

static inline void spi_disable(struct spi * dev)
{
        dev->CR1 &= ~BIT(6);
}

//--------------------------------| SPI_CR2 |---------------------------------//

enum spi_frf {
        SPI_FRF_MOTOROLA,
        SPI_FRF_TI
};

enum spi_frxth {
        SPI_FRXTH_16,
        SPI_FRXTH_8
};

enum spi_ldma {
        SPI_LDMA_EVEN,
        SPI_LDMA_ODD
};

struct spi_cr2_init {
        union {
                struct {
                        unsigned rx_dma_en      : 1;
                        unsigned tx_dma_en      : 1;
                        unsigned ss_oe          : 1;
                        unsigned nssp           : 1;
                        enum spi_frf frf        : 1;
                        unsigned err_ie         : 1;
                        unsigned rx_ne_ie       : 1;
                        unsigned tx_e_ie        : 1;
                        unsigned ds             : 4;
                        enum spi_frxth frx_th   : 1;
                        enum spi_ldma ldma_rx   : 1;
                        enum spi_ldma ldma_tx   : 1;
                };
                unsigned short reg_val;
        };
};

static inline void spi_init_cr2(struct spi * dev, struct spi_cr2_init init)
{
        dev->CR2 = init.reg_val;
}

static inline void spi_set_frame_format(struct spi * dev, enum spi_frf frf)
{
        dev->CR2 &= ~BIT(4);
        dev->CR2 |= (frf & 1) << 4;
}

static inline void spi_enable_ss(struct spi * dev)
{
        dev->CR2 |= BIT(2);
}

static inline void spi_set_data_size(struct spi * dev, unsigned char dat_sz)
{
        dev->CR2 &= ~(0xF << 8);
        dev->CR2 |= (dat_sz & 0xF) << 8;
}

//---------------------------------| SPI_SR |---------------------------------//

enum spi_fifo_lv {
        SPI_FIFO_LV_EMPTY,
        SPI_FIFO_LV_1_4,
        SPI_FIFO_LV_1_2,
        SPI_FIFO_LV_FULL
};

static inline int spi_is_ready_tx(struct spi * dev)
{
        return dev->SR & BIT(1);
}

static inline int spi_is_ready_rx(struct spi * dev)
{
        return dev->SR & BIT(0);
}

static inline enum spi_fifo_lv spi_get_tx_fifo_lv(struct spi * dev)
{
        return (dev->SR >> 11) & 0x3;
}

static inline enum spi_fifo_lv spi_get_rx_fifo_lv(struct spi * dev)
{
        return (dev->SR >> 9) & 0x3;
}

static inline int spi_is_busy(struct spi * dev)
{
        return dev->SR & BIT(7);
}

//---------------------------------| SPI_DR |---------------------------------//

static inline void spi_write(struct spi * dev, unsigned char data)
{
        *(unsigned char *)&dev->DR = data & 0xFF;
}

static inline unsigned char spi_read(struct spi * dev)
{
        return *(unsigned char *)&dev->DR & 0xFF;
}

//-------------------------------| SPI_CRCPR |--------------------------------//

//------------------------------| SPI_RXCRCR |--------------------------------//

//------------------------------| SPI_TXCRCR |--------------------------------//

#endif // HW_SPI_H_