/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2024 Lars Görner */

#include "../utils/utils.h"
#include "../utils/delay.h"
#include "../hw/rtc.h"
#include "../hw/nvic.h"
#include "../hw/exti.h"
#include "hw_init.h"
#include "display.h"
#include "input.h"
#include "edit_init_date.h"
#include "assets/graphics.h"

static const char main_screen_msg_start[] = "Nur noch";
static const char main_screen_msg_end[] = "Tage";
static const char main_screen_msg_final_end[] = "Tag";
static const char main_screen_msg_gratulation[] = "Du hast es geschafft!!!";

void __isr nvic_rtc_handler(void)
{
        rtc_clear_alarm_flag();
        exti_ack_pending(EXTI_LINE_17);
        nvic_clear_pending_interrupt(NVIC_IR_2);
}

// d2 - d1
static unsigned get_date_diff_days(struct rtc_date * date1, struct rtc_date * date2)
{
        unsigned y1, y2, m1, m2, d1, d2;
        unsigned num_days_d1, num_days_d2;

        BCD2UINT(date2->year_tens, date2->year_units, y2);
        BCD2UINT(date1->year_tens, date1->year_units, y1);
        BCD2UINT(date2->month_tens, date2->month_units, m2);
        BCD2UINT(date1->month_tens, date1->month_units, m1);
        BCD2UINT(date2->day_tens, date2->day_units, d2);
        BCD2UINT(date1->day_tens, date1->day_units, d1);

        num_days_d1 = (146097 * y1) / 400 + (153 * m1 + 8) / 5 + d1;
        num_days_d2 = (146097 * y2) / 400 + (153 * m2 + 8) / 5 + d2;

        return num_days_d2 - num_days_d1;
}

static void print_main_screen(void)
{
        char cur_date_str[] = "00.00.2000";
        char rem_days_str[] = "0000";
        unsigned rem_days;
        unsigned char has_rem_days;
        unsigned char rem_days_str_offs = 0;

        while (!rtc_is_regs_synced());
        struct rtc_date cur_date = rtc_get_date();

        // set cur date string
        cur_date_str[0] = cur_date.day_tens + '0';
        cur_date_str[1] = cur_date.day_units + '0';
        cur_date_str[3] = cur_date.month_tens + '0';
        cur_date_str[4] = cur_date.month_units + '0';
        cur_date_str[8] = cur_date.year_tens + '0';
        cur_date_str[9] = cur_date.year_units + '0';

        // calc days
        rem_days = get_date_diff_days(&cur_date, &end_date);
        has_rem_days = rem_days > 0 ? 1 : 0;
        while (rem_days >= 1000) {
                rem_days_str[0]++;
                rem_days -= 1000;
        }
        while (rem_days >= 100) {
                rem_days_str[1]++;
                rem_days -= 100;
        }
        while (rem_days >= 10) {
                rem_days_str[2]++;
                rem_days -= 10;
        }
        rem_days_str[3] = rem_days + '0';

        for (rem_days_str_offs = 0; rem_days_str_offs < 4; rem_days_str_offs++) {
                if (rem_days_str[rem_days_str_offs] != '0') {
                        break;
                }
        }

        // print
        display_start();
        display_draw_bg();
        if (has_rem_days) {
                display_draw_text(3 * TILE_WIDTH, 7 * TILE_HEIGHT, main_screen_msg_start);
                display_draw_text_big((12 + rem_days_str_offs) * TILE_WIDTH, 6 * TILE_HEIGHT, 
                                      &rem_days_str[rem_days_str_offs]);
                if (rem_days > 1) {
                        display_draw_text(17 * TILE_WIDTH, 7 * TILE_HEIGHT, main_screen_msg_end);
                } else {
                        display_draw_text(17 * TILE_WIDTH, 7 * TILE_HEIGHT, main_screen_msg_final_end);
                }
        } else {
                display_draw_text(TILE_WIDTH, 7 * TILE_HEIGHT, main_screen_msg_gratulation);
        }

        // current date
        //display_draw_text(4 * TILE_WIDTH, 13 * TILE_HEIGHT, get_day_of_week(&cur_date));
        display_draw_text(14 * TILE_WIDTH, 13 * TILE_HEIGHT, cur_date_str);

        display_trigger_update(WF_MODE_GC);
        display_stop();
}

void __noreturn main(void)
{
        hw_init();

        //battery_init();
        display_init();
        input_init();

        // display white clear
        display_start();
        display_clear();
        display_stop();


        enter_init_date_enter_routine();

        // setup rtc alarm a interrupt
        exti_enable_line_interrupt(EXTI_LINE_17);
        exti_enable_rising_trigger_event(EXTI_LINE_17);
        nvic_enable_interrupt(NVIC_IR_2);
        rtc_enable_alarm_a();

        while(1) {
                print_main_screen();
                __WFI();
        }
}