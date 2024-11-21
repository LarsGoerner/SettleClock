/* SPDX-License-Identifier: MIT */
/* Copyright (c) Lars Görner */

#ifndef APP_DISPLAY_H_
#define APP_DISPLAY_H_

#define DISPLAY_WIDTH      800
#define DISPLAY_HEIGHT     480

enum wf_mode {
        WF_MODE_GC = 0xF7,
        WF_MODE_DU = 0xFF
};

void display_init(void);
void display_start(void);
void display_stop(void);
void display_clear(void);
void display_send_image(unsigned short x, unsigned short y, 
                        unsigned short w, unsigned short h, 
                        const void * buf);
void display_trigger_update(enum wf_mode wfm);

void display_draw_bg(void);
void display_draw_text(unsigned short x, unsigned short y, const char * txt);
void display_draw_text_big(unsigned short x, unsigned short y, const char * txt);

#endif // APP_DISPLAY_H_