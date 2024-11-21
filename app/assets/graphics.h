/* SPDX-License-Identifier: MIT */
/* Copyright (c) Lars Görner */

#ifndef APP_ASSETS_GRAPHICS_H_
#define APP_ASSETS_GRAPHICS_H_

#include "../display.h"

#define TILE_WIDTH              32
#define TILE_HEIGHT             32
#define PX_PER_BYTE             8
#define TILE_SIZE               (TILE_WIDTH * TILE_HEIGHT / PX_PER_BYTE)

#define TILE_MAP_WIDTH          (DISPLAY_WIDTH / TILE_WIDTH)
#define TILE_MAP_HEIGHT         (DISPLAY_HEIGHT / TILE_HEIGHT)

//---| Background tiles
const unsigned char * graphics_bg_get(unsigned char id);

//---| Font tiles
const unsigned char * graphics_font32_get(char c);
const unsigned char * graphics_font_2_32_get(char c);


#endif // APP_ASSETS_GRAPHICS_H_