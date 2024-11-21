/* SPDX-License-Identifier: MIT */
/* Copyright (c) Lars Görner */

#include "../utils/delay.h"
#include "../hw/spi.h"
#include "../hw/ssd1677.h"
#include "../hw/gpio.h"
#include "display.h"
#include "assets/graphics.h"

#define DSP_BUS         SPI1
#define DSP_GP_PORT     GPIOA
#define DSP_RST_PIN     GPIO_PIN_10
#define DSP_BUSY_PIN    GPIO_PIN_9
#define DSP_DC_PIN      GPIO_PIN_6
#define DSP_CS_PIN      GPIO_PIN_4

static unsigned char TX_BUF[5];

//---| GPIO Functions

static inline void display_hw_rst(void)
{
        gpio_set_pin(DSP_GP_PORT, DSP_RST_PIN);
        delay_ms(100);
        gpio_clr_pin(DSP_GP_PORT, DSP_RST_PIN);
        delay_ms(2);
        gpio_set_pin(DSP_GP_PORT, DSP_RST_PIN);
        delay_ms(100);
}

static inline void display_set_dc_data(void)
{
        gpio_set_pin(DSP_GP_PORT, DSP_DC_PIN);
}

static inline void display_set_dc_command(void)
{
        gpio_clr_pin(DSP_GP_PORT, DSP_DC_PIN);
}

static inline void display_wait_busy(void)
{
        while (gpio_get_val(DSP_GP_PORT, DSP_BUSY_PIN));
}

static inline void display_set_cs(void)
{
        gpio_set_pin(DSP_GP_PORT, DSP_CS_PIN);
}

static inline void display_clr_cs(void)
{
        gpio_clr_pin(DSP_GP_PORT, DSP_CS_PIN);
}

//---| SPI Functions

static void spi_start(void)
{
        spi_enable(DSP_BUS);
}

static void spi_wait_write_done(void)
{
        while (spi_get_tx_fifo_lv(DSP_BUS) != SPI_FIFO_LV_EMPTY);
        while (spi_is_busy(DSP_BUS));
}

static void spi_stop(void)
{
        spi_wait_write_done();
        spi_disable(DSP_BUS);
}

static void spi_send(const void * buf, unsigned len)
{
        const unsigned char * bptr = buf;
        while (len--) {
                while (!spi_is_ready_tx(DSP_BUS));
                spi_write(DSP_BUS, *bptr++);
        }
}

static void display_bus_write_cmd(unsigned char cmd)
{
        display_clr_cs();
        spi_start();
        display_set_dc_command();
        spi_send(&cmd, sizeof(cmd));
        spi_stop();
        display_set_cs();
}

static void display_bus_write_cmd_data(unsigned char cmd, const void * buf, unsigned buf_sz)
{
        display_clr_cs();
        spi_start();
        display_set_dc_command();
        spi_send(&cmd, sizeof(cmd));
        spi_wait_write_done();
        display_set_dc_data();
        spi_send(buf, buf_sz);
        spi_stop();
        display_set_cs();
}

//---| Display Functions

static void display_set_window(unsigned short x, unsigned short y, 
                               unsigned short w, unsigned short h)
{
        // set X RAM address
        TX_BUF[0] = x & 0xFF;
        TX_BUF[1] = (x >> 8) & 0x3;
        TX_BUF[2] = (x + w - 1) & 0xFF;
        TX_BUF[3] = ((x + w - 1) >> 8) & 0x3;
        display_bus_write_cmd_data(SSD1677_CMD_RAM_X, TX_BUF, 4);

        // set Y RAM address
        TX_BUF[0] = (y + h - 1) & 0xFF;
        TX_BUF[1] = ((y + h - 1) >> 8) & 0x3;
        TX_BUF[2] = y & 0xFF;
        TX_BUF[3] = (y >> 8) & 0x3;
        display_bus_write_cmd_data(SSD1677_CMD_RAM_Y, TX_BUF, 4);
}

static void display_set_cursor(unsigned short x, unsigned short y)
{
        TX_BUF[0] = x & 0xFF;
        TX_BUF[1] = x >> 8;
        display_bus_write_cmd_data(SSD1677_CMD_RAM_X_C, TX_BUF, 2);

        y = DISPLAY_HEIGHT - y - 1;
        TX_BUF[0] = y & 0xFF;
        TX_BUF[1] = y >> 8;
        display_bus_write_cmd_data(SSD1677_CMD_RAM_Y_C, TX_BUF, 2);
}

void display_init(void)
{
        
}

void display_start(void)
{
        // Set initial configuration
        display_hw_rst();
        display_wait_busy();
        display_bus_write_cmd(SSD1677_CMD_SWR);
        display_wait_busy();

        // sense temp (cmd 0x18)
        TX_BUF[0] = 0x80;
        display_bus_write_cmd_data(SSD1677_CMD_TSC, TX_BUF, 1);

        // Set soft start
        TX_BUF[0] = 0xAE;
        TX_BUF[1] = 0xC7;
        TX_BUF[2] = 0xC3;
        TX_BUF[3] = 0xC0;
        TX_BUF[4] = 0x80;
        display_bus_write_cmd_data(SSD1677_CMD_BSSC, TX_BUF, 5);

        // set gd (cmd 0x01)
        TX_BUF[0] = (DISPLAY_HEIGHT - 1) & 0xFF;
        TX_BUF[1] = ((DISPLAY_HEIGHT - 1) >> 8) & 0xFF;
        TX_BUF[2] = 0x02;
        display_bus_write_cmd_data(SSD1677_CMD_DOC, TX_BUF, 3);

        // set panel border (cmd 0x3C)
        TX_BUF[0] = 0x01;
        display_bus_write_cmd_data(SSD1677_CMD_BWC, TX_BUF, 1);

        // set display RAM size (cmd 0x11, 0x44, 0x45)
        TX_BUF[0] = 0x01;
        display_bus_write_cmd_data(SSD1677_CMD_DEMS, TX_BUF, 1);
        
        display_set_window(0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT);
        display_set_cursor(0, 0);

        // wait busy low
        display_wait_busy();
}

void display_stop(void)
{
        // Power off
        // deep sleep (cmd 0x10)
        display_bus_write_cmd(SSD1677_CMD_DSM);
        // power off
}

void display_clear(void)
{
        // auto write RED
        TX_BUF[0] = 0xE7;
        display_bus_write_cmd_data(SSD1677_CMD_AWRR, TX_BUF, 1);
        display_wait_busy();

        // auto write BW
        display_bus_write_cmd_data(SSD1677_CMD_AWBWR, TX_BUF, 1);
        display_wait_busy();

        display_trigger_update(WF_MODE_GC);
}

void display_send_image(unsigned short x, unsigned short y, 
                        unsigned short w, unsigned short h,
                        const void * buf)
{
        display_set_window(x, y, w, h);
        display_set_cursor(x, y);
        display_bus_write_cmd_data(SSD1677_CMD_RAM_BW_WR, buf, w * h / 8);
}

void display_trigger_update(enum wf_mode wfm)
{
        TX_BUF[0] = wfm;
        // drive display panel (cmd 0x22, 0x20)
        display_bus_write_cmd_data(SSD1677_CMD_DUC2, TX_BUF, 1);
        display_bus_write_cmd(SSD1677_CMD_MA);
        // wait busy
        display_wait_busy();
}

// Drawing functions

static const unsigned char BG[TILE_MAP_WIDTH * TILE_MAP_HEIGHT] = {
        0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2,
        3, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 4,
        3, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 4,
        3, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 4,
        3, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 4,
        3, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 4,
        3, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 4,
        3, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 4,
        3, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 4,
        3, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 4,
        3, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 4,
        3, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 4,
        3, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 4,
        3, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 5, 4,
        6, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 7, 8
};

void display_draw_bg(void)
{
        register unsigned map_x, map_y;
        const unsigned char * bg_map = BG;

        for (map_y = 0; map_y < TILE_MAP_HEIGHT; map_y++) {
                for (map_x = 0; map_x < TILE_MAP_WIDTH; map_x++) {
                        display_send_image(
                                map_x * TILE_WIDTH, map_y * TILE_HEIGHT,
                                TILE_WIDTH, TILE_HEIGHT,
                                graphics_bg_get(*bg_map++));
                }
        }
}

void display_draw_text(unsigned short x, unsigned short y, const char * txt)
{
        unsigned short tile_x = x;
        unsigned short tile_y = y;
        while (*txt != '\0') {
                if (*txt == '\n') {
                        tile_y += 2 * TILE_HEIGHT;
                        tile_x = x;
                        ++txt;
                } else {
                        display_send_image(tile_x, tile_y, TILE_WIDTH, TILE_HEIGHT, 
                                           graphics_font32_get(*txt++));
                        tile_x += TILE_WIDTH;
                }
        }
}

void display_draw_text_big(unsigned short x, unsigned short y, const char * txt)
{
        while (*txt != '\0') {
                display_send_image(x, y, TILE_WIDTH, 2 * TILE_HEIGHT, 
                                   graphics_font_2_32_get(*txt++));
                x += TILE_WIDTH;
        }
}