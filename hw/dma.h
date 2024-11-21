/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2024 Lars Görner */

#ifndef HW_DMA_H_
#define HW_DMA_H_

#include "mem_adr.h"

struct dma_isr {
        uint32_t gif1           : 1;
        uint32_t tcif1          : 1;
        uint32_t htif1          : 1;
        uint32_t teif1          : 1;
        uint32_t gif2           : 1;
        uint32_t tcif2          : 1;
        uint32_t htif2          : 1;
        uint32_t teif2          : 1;

        uint32_t gif3           : 1;
        uint32_t tcif3          : 1;
        uint32_t htif3          : 1;
        uint32_t teif3          : 1;
        uint32_t gif4           : 1;
        uint32_t tcif4          : 1;
        uint32_t htif4          : 1;
        uint32_t teif4          : 1;

        uint32_t gif5           : 1;
        uint32_t tcif5          : 1;
        uint32_t htif5          : 1;
        uint32_t teif5          : 1;
        uint32_t                : 4;

        uint32_t                : 8;
};

struct dma_ifcr {
        uint32_t cgif1          : 1;
        uint32_t ctcif1         : 1;
        uint32_t chtif1         : 1;
        uint32_t cteif1         : 1;
        uint32_t cgif2          : 1;
        uint32_t ctcif2         : 1;
        uint32_t chtif2         : 1;
        uint32_t cteif2         : 1;

        uint32_t cgif3          : 1;
        uint32_t ctcif3         : 1;
        uint32_t chtif3         : 1;
        uint32_t cteif3         : 1;
        uint32_t cgif4          : 1;
        uint32_t ctcif4         : 1;
        uint32_t chtif4         : 1;
        uint32_t cteif4         : 1;

        uint32_t cgif5          : 1;
        uint32_t ctcif5         : 1;
        uint32_t chtif5         : 1;
        uint32_t cteif5         : 1;
        uint32_t                : 4;

        uint32_t                : 8;
};

struct dma_ccr {
        uint32_t en             : 1;
        uint32_t tcie           : 1;
        uint32_t htie           : 1;
        uint32_t teie           : 1;
        uint32_t dir            : 1;
        uint32_t circ           : 1;
        uint32_t pinc           : 1;
        uint32_t minc           : 1;

        uint32_t psize          : 2;
        uint32_t msize          : 2;
        uint32_t pl             : 2;
        uint32_t mem2mem        : 1;
        uint32_t                : 1;

        uint32_t                : 16;
};

struct dma_cndtr {
        uint32_t ndt            : 16;
        uint32_t                : 16;
};

struct dma_cselr {
        uint32_t c1s            : 4;
        uint32_t c2s            : 4;

        uint32_t c3s            : 4;
        uint32_t c4s            : 4;

        uint32_t c5s            : 4;
        uint32_t                : 4;

        uint32_t                : 8;
};

struct dma {
        struct dma_isr is;
        struct dma_ifcr ifc;

        struct dma_ccr cc1;
        struct dma_cndtr cndt1;
        uint32_t cpar1;
        uint32_t cmar1;
        uint32_t : 32;

        struct dma_ccr cc2;
        struct dma_cndtr cndt2;
        uint32_t cpar2;
        uint32_t cmar2;
        uint32_t : 32;

        struct dma_ccr cc3;
        struct dma_cndtr cndt3;
        uint32_t cpar3;
        uint32_t cmar3;
        uint32_t : 32;

        struct dma_ccr cc4;
        struct dma_cndtr cndt4;
        uint32_t cpar4;
        uint32_t cmar4;
        uint32_t : 32;

        struct dma_ccr cc5;
        struct dma_cndtr cndt5;
        uint32_t cpar5;
        uint32_t cmar5;

        uint32_t reserved[60];

        struct dma_cselr csel;
};
static volatile struct dma * const DMA = (struct dma *)DMA_BASE_ADDR;

#endif // HW_DMA_H_