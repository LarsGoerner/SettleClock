/* SPDX-License-Identifier: MIT */
/* Copyright (c) Lars Görner */

#include "display.h"
#include "assets/graphics.h"
#include "edit_init_date.h"
#include "input.h"
#include "../hw/rtc.h"

struct rtc_date init_date = { 
        .day_tens = 0,
        .day_units = 1,
        .month_tens = 0,
        .month_units = 1,
        .year_tens = 2,
        .year_units = 4
};

struct rtc_time init_time = {
        .pm = RTC_AM_24
};

struct rtc_date end_date = {
        .day_tens = 0,
        .day_units = 1,
        .month_tens = 0,
        .month_units = 1,
        .year_tens = 2,
        .year_units = 4
};

static const char init_date_msg[] = "Welcher Tag ist heute?";
static const char init_time_msg[] = "Welche Uhrzeit haben\nwir gerade?";
static const char end_date_msg[] = "An welchem Tag hast du\nes geschafft?";
static const char loading_msg[] = "Danke.\nDer Timer wird\neingerichtet...";

static void rtc_clock_init(struct rtc_date * init_date, struct rtc_time * init_time)
{
        // enter init mode
        rtc_enable_init_mode();
        while(!rtc_is_init_mode());

        // set prescaler
        rtc_set_prediv_async(99); // \/
        rtc_set_prediv_sync(399); // -+--> 40000 / ((99 + 1) * (399 + 1)) = 1Hz

        // set initial time
        rtc_set_time(*init_time);
        rtc_set_date(*init_date);
        rtc_set_fmt(RTC_FMT_24);

        // set alarm
        rtc_disable_alarm_a();
        while (!rtc_is_writable_alarm_a());
        rtc_set_alarm_a((struct rtc_date){ 0 }, (struct rtc_time){ 0 }, RTC_MASK_DAY);
        rtc_enable_alarm_a_irq();

        // exit init mode
        rtc_disable_init_mode();
}

static void date_edit_mode(const char * msg, struct rtc_date * date)
{
        char cbuf[] = "0000";
        unsigned cur_pos = 0;
        const unsigned csr_pos_lut[] = { 
                7.5 * TILE_WIDTH, 10.5 * TILE_WIDTH, 14.5 * TILE_WIDTH, 17 * TILE_WIDTH };
        const unsigned num_pos_y = 8 * TILE_HEIGHT;
        unsigned date_tmp_val;

        while(1) {
                display_draw_bg();
                display_draw_text(2 * TILE_WIDTH, 3 * TILE_HEIGHT, msg);

                // day
                cbuf[0] = date->day_tens + '0';
                cbuf[1] = date->day_units + '0';
                cbuf[2] = '\0';
                display_draw_text_big(7 * TILE_WIDTH, num_pos_y, cbuf);
                cbuf[0] = date->month_tens + '0';
                cbuf[1] = date->month_units + '0';
                display_draw_text_big(10 * TILE_WIDTH, num_pos_y, cbuf);
                cbuf[0] = '2';
                cbuf[1] = '0';
                cbuf[2] = date->year_tens + '0';
                cbuf[3] = date->year_units + '0';
                display_draw_text_big(13 * TILE_WIDTH, num_pos_y, cbuf);

                // dots
                cbuf[0] = '.';
                cbuf[1] = '\0';
                display_draw_text(9 * TILE_WIDTH, num_pos_y + TILE_HEIGHT, cbuf);
                display_draw_text(12 * TILE_WIDTH, num_pos_y + TILE_HEIGHT, cbuf);

                // cursor
                cbuf[0] = 1;
                display_draw_text(csr_pos_lut[cur_pos], num_pos_y - TILE_HEIGHT, cbuf);
                cbuf[0] = 2;
                display_draw_text(csr_pos_lut[cur_pos], num_pos_y + 2 * TILE_HEIGHT, cbuf);
                if (cur_pos == 2) {
                        cbuf[0] = 3;
                        display_draw_text(csr_pos_lut[cur_pos + 1], num_pos_y + TILE_HEIGHT, cbuf);
                }

                display_trigger_update(WF_MODE_DU);
                input_enable();
                __WFI();
                input_disable();
                if (pending_inputs.left_key) {
                        if (cur_pos > 0) {
                                cur_pos--;
                        }
                } else if (pending_inputs.up_key) {
                        switch (cur_pos) {
                        case 0: // day
                                BCD2UINT(date->day_tens, date->day_units, date_tmp_val);
                                if (date_tmp_val >= 31) {
                                        date_tmp_val = 1;
                                } else {
                                        date_tmp_val++;
                                }
                                UINT2BCD(date_tmp_val, date->day_tens, date->day_units);
                                break;
                        case 1: // month
                                BCD2UINT(date->month_tens, date->month_units, date_tmp_val);
                                if (date_tmp_val >= 12) {
                                        date_tmp_val = 1;
                                } else {
                                        date_tmp_val++;
                                }
                                UINT2BCD(date_tmp_val, date->month_tens, date->month_units);
                                break;
                        case 2: // year
                                BCD2UINT(date->year_tens, date->year_units, date_tmp_val);
                                if (date_tmp_val >= 99) {
                                        date_tmp_val = 0;
                                } else {
                                        date_tmp_val++;
                                }
                                UINT2BCD(date_tmp_val, date->year_tens, date->year_units);
                                break;
                        default:
                                break;
                        }
                } else if (pending_inputs.down_key) {
                        switch (cur_pos) {
                        case 0: // day
                                BCD2UINT(date->day_tens, date->day_units, date_tmp_val);
                                if (date_tmp_val == 1) {
                                        date_tmp_val = 31;
                                } else {
                                        date_tmp_val--;
                                }
                                UINT2BCD(date_tmp_val, date->day_tens, date->day_units);
                                break;
                        case 1: // month
                                BCD2UINT(date->month_tens, date->month_units, date_tmp_val);
                                if (date_tmp_val <= 1) {
                                        date_tmp_val = 12;
                                } else {
                                        date_tmp_val--;
                                }
                                UINT2BCD(date_tmp_val, date->month_tens, date->month_units);
                                break;
                        case 2: // year
                                BCD2UINT(date->year_tens, date->year_units, date_tmp_val);
                                if (date_tmp_val == 0) {
                                        date_tmp_val = 99;
                                } else {
                                        date_tmp_val--;
                                }
                                UINT2BCD(date_tmp_val, date->year_tens, date->year_units);
                                break;
                        default:
                                break;
                        }
                } else if (pending_inputs.right_key) {
                        if (cur_pos < 2) {
                                cur_pos++;
                        } else {
                                input_ack_inputs();
                                return;
                        }
                }
                input_ack_inputs();
        }
}

static void time_edit_mode(const char * msg, struct rtc_time * time)
{
        char cbuf[] = "00:00";
        unsigned cur_pos = 0;
        const unsigned csr_pos_lut[] = { 
                7.5 * TILE_WIDTH, 10.5 * TILE_WIDTH, 12 * TILE_WIDTH};
        const unsigned num_pos_y = 8 * TILE_HEIGHT;
        unsigned time_tmp_val;

        while(1) {
                display_draw_bg();
                display_draw_text(2 * TILE_WIDTH, 3 * TILE_HEIGHT, msg);

                cbuf[0] = time->hour_tens + '0';
                cbuf[1] = time->hour_units + '0';
                cbuf[3] = time->min_tens + '0';
                cbuf[4] = time->min_units + '0';
                display_draw_text_big(7 * TILE_WIDTH, num_pos_y, cbuf);

                // cursor
                cbuf[0] = 1;
                cbuf[1] = '\0';
                display_draw_text(csr_pos_lut[cur_pos], num_pos_y - TILE_HEIGHT, cbuf);
                cbuf[0] = 2;
                display_draw_text(csr_pos_lut[cur_pos], num_pos_y + 2 * TILE_HEIGHT, cbuf);
                if (cur_pos == 1) {
                        cbuf[0] = 3;
                        display_draw_text(csr_pos_lut[cur_pos + 1], num_pos_y + TILE_HEIGHT, cbuf);
                }

                display_trigger_update(WF_MODE_DU);
                input_enable();
                __WFI();
                input_disable();
                if (pending_inputs.left_key) {
                        if (cur_pos > 0) {
                                cur_pos--;
                        }
                } else if (pending_inputs.up_key) {
                        switch (cur_pos) {
                        case 0: // hour
                                BCD2UINT(time->hour_tens, time->hour_units, time_tmp_val);
                                if (time_tmp_val >= 23) {
                                        time_tmp_val = 0;
                                } else {
                                        time_tmp_val++;
                                }
                                UINT2BCD(time_tmp_val, time->hour_tens, time->hour_units);
                                break;
                        case 1: // min
                                BCD2UINT(time->min_tens, time->min_units, time_tmp_val);
                                if (time_tmp_val >= 59) {
                                        time_tmp_val = 1;
                                } else {
                                        time_tmp_val++;
                                }
                                UINT2BCD(time_tmp_val, time->min_tens, time->min_units);
                                break;
                        default:
                                break;
                        }
                } else if (pending_inputs.down_key) {
                        switch (cur_pos) {
                        case 0: // hour
                                BCD2UINT(time->hour_tens, time->hour_units, time_tmp_val);
                                if (time_tmp_val == 0) {
                                        time_tmp_val = 23;
                                } else {
                                        time_tmp_val--;
                                }
                                UINT2BCD(time_tmp_val, time->hour_tens, time->hour_units);
                                break;
                        case 1: // min
                                BCD2UINT(time->min_tens, time->min_units, time_tmp_val);
                                if (time_tmp_val <= 0) {
                                        time_tmp_val = 59;
                                } else {
                                        time_tmp_val--;
                                }
                                UINT2BCD(time_tmp_val, time->min_tens, time->min_units);
                                break;
                        default:
                                break;
                        }
                } else if (pending_inputs.right_key) {
                        if (cur_pos < 1) {
                                cur_pos++;
                        } else {
                                input_ack_inputs();
                                return;
                        }
                }
                input_ack_inputs();
        }
}

void enter_init_date_enter_routine(void)
{
        display_start();
        date_edit_mode(init_date_msg, &init_date);
        time_edit_mode(init_time_msg, &init_time);
        date_edit_mode(end_date_msg, &end_date);
        
        display_draw_bg();
        display_draw_text(2 * TILE_WIDTH, 5 * TILE_HEIGHT, loading_msg);
        display_trigger_update(WF_MODE_DU);

        display_stop();

        rtc_clock_init(&init_date, &init_time);
}