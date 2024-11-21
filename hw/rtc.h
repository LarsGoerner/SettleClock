/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2024 Lars Görner */

#ifndef HW_RTC_H_
#define HW_RTC_H_

#include "../utils/utils.h"

struct rtc {
        volatile unsigned TR;
        volatile unsigned DR;
        volatile unsigned CR;
        volatile unsigned ISR;
        volatile unsigned PRER;
        volatile unsigned WUTR;
        volatile unsigned reserved0;
        volatile unsigned ALRMAR;
        volatile unsigned reserved1;
        volatile unsigned WPR;
        volatile unsigned SSR;
        volatile unsigned SHIFTR;
        volatile unsigned TSTR;
        volatile unsigned TSDR;
        volatile unsigned TSSSR;
        volatile unsigned CALR;
        volatile unsigned TAFCR;
        volatile unsigned ALRMASSR;
        volatile unsigned reserved2;
        volatile unsigned OR;
};
#define RTC     ((struct rtc *)0x40002800)

enum rtc_am_pm {
        RTC_AM_24,
        RTC_PM
};

/** @brief BCD formated time representation */
struct rtc_time {
        union {
                struct {
                        unsigned sec_units       : 4; /**< First digit */
                        unsigned sec_tens        : 3; /**< Second digit */
                        unsigned                 : 1;

                        unsigned min_units       : 4; /**< First digit */
                        unsigned min_tens        : 3; /**< Second digit */
                        unsigned                 : 1;

                        unsigned hour_units      : 4; /**< First digit */
                        unsigned hour_tens       : 2; /**< Second digit */
                        enum rtc_am_pm pm       : 1;
                        unsigned                 : 1;
                };
                unsigned reg_val;
        };
};

enum rtc_week_day {
        RTC_MONDAY = 1,
        RTC_TUESDAY,
        RTC_WEDNESDAY,
        RTC_THURSDAY,
        RTC_FRIDAY,
        RTC_SATURDAY,
        RTC_SUNDAY
};

/** @brief BCD formated date representation */
struct rtc_date {
        union {
                struct {
                        unsigned day_units       : 4; /**< First digit */
                        unsigned day_tens        : 2; /**< Second digit */
                        unsigned                 : 2;

                        unsigned month_units     : 4; /**< First digit */
                        unsigned month_tens      : 1; /**< Second digit */
                        enum rtc_week_day week_day : 3;

                        unsigned year_units      : 4; /**< First digit */
                        unsigned year_tens       : 4; /**< Second digit */
                };
                unsigned reg_val;
        };
};

//---| RTC time register

static inline void rtc_set_time(struct rtc_time time)
{
        RTC->TR = time.reg_val;
}

static inline struct rtc_time rtc_get_time(void)
{
        return (struct rtc_time) { .reg_val = RTC->TR };
}

//---| RTC date register

static inline void rtc_set_date(struct rtc_date date)
{
        RTC->DR = date.reg_val;
}

static inline struct rtc_date rtc_get_date(void)
{
        return (struct rtc_date) { .reg_val = RTC->DR };
}

//---| RTC control register

enum rtc_fmt {
        RTC_FMT_24,
        RTC_FMT_AMFM
};

enum rtc_wucksel {
        RTC_WUCKSEL_DIV_16,
        RTC_WUCKSEL_DIV_8,
        RTC_WUCKSEL_DIV_4,
        RTC_WUCKSEL_DIV_2,
        RTC_WUCKSEL_DIV_1
};

static inline void rtc_set_fmt(enum rtc_fmt fmt)
{
        RTC->CR &= ~BIT(6);
        RTC->CR |= (fmt << 6);
}

static inline void rtc_set_wucksel(enum rtc_wucksel ws)
{
        RTC->CR &= ~0x7;
        RTC->CR |= ws & 0x7;
}

static inline void rtc_enable_wut(void)
{
        RTC->CR |= BIT(10);
}

static inline void rtc_disable_wut(void)
{
        RTC->CR &= ~BIT(10);
}

static inline void rtc_enable_alarm_a_irq(void)
{
        RTC->CR |= BIT(12);
}
static inline void rtc_disable_alarm_a_irq(void)
{
        RTC->CR &= ~BIT(12);
}

static inline void rtc_enable_alarm_a(void)
{
        RTC->CR |= BIT(8);
}

static inline void rtc_disable_alarm_a(void)
{
        RTC->CR &= ~BIT(8);
}

//---| RTC initialization & status register

static inline void rtc_clear_alarm_flag(void)
{
        RTC->ISR &= ~BIT(8);
}

static inline void rtc_enable_init_mode(void)
{
        RTC->ISR |= BIT(7);
}

static inline void rtc_disable_init_mode(void)
{
        RTC->ISR &= ~BIT(7);
}

static inline int rtc_is_init_mode(void)
{
        return RTC->ISR & BIT(6);
}

static inline int rtc_is_regs_synced(void)
{
        return RTC->ISR & BIT(5);
}

static inline int rtc_is_writable_wut(void)
{
        return RTC->ISR & BIT(2);
}

static inline int rtc_is_writable_alarm_a(void)
{
        return RTC->ISR & BIT(0);
}

//---| RTC prescaler register

static inline void rtc_set_prediv_sync(unsigned short div)
{
        RTC->PRER &= ~0x7FFF;
        RTC->PRER |= div & 0x7FFF;
}

static inline void rtc_set_prediv_async(unsigned char div)
{
        RTC->PRER &= ~(0x7F << 16);
        RTC->PRER |= (div & 0x7F) << 16;
}

//---| RTC wake-up timer register

static inline void rtc_set_wut(unsigned short val)
{
        RTC->PRER &= ~0xFFFF;
        RTC->PRER |= val & 0xFFFF;
}

//---| RTC alarm A register


#define RTC_MASK_DAY            BIT(31)
#define RTC_MASK_HOURS          BIT(23)
#define RTC_MASK_MINUTES        BIT(15)
#define RTC_MASK_SECONDS        BIT(7)

static inline void rtc_set_alarm_a(struct rtc_date d, struct rtc_time t, unsigned msk)
{
        register unsigned reg_val = 0;
        
        // set date time
        reg_val |= (d.day_tens & 0x3) << 28;
        reg_val |= (d.day_units & 0xF) << 24;

        reg_val |= (t.pm & 1) << 22;
        reg_val |= (t.hour_tens & 0x3) << 20;
        reg_val |= (t.hour_units & 0xF) << 16;
        reg_val |= (t.min_tens & 0x7) << 12;
        reg_val |= (t.min_units & 0xF) << 8;
        reg_val |= (t.sec_tens & 0x7) << 4;
        reg_val |= (t.sec_units & 0xF) << 0;

        reg_val |= msk;
        
        RTC->ALRMAR = reg_val;
}

//---| RTC write protection register

static inline void rtc_unlock_write_protection(void)
{
        *((volatile unsigned short *)&RTC->WPR) = 0xCA;
        *((volatile unsigned short *)&RTC->WPR) = 0x53;
}

static inline void rtc_lock_write_protection(void)
{
        *((volatile unsigned short *)&RTC->WPR) = 0xFE;
        *((volatile unsigned short *)&RTC->WPR) = 0x64;
}

//---| RTC sub second register

//---| RTC shift control register

//---| RTC timestamp time register

static inline struct rtc_time rtc_get_timestamp_time(void)
{
        return (struct rtc_time) {.reg_val = RTC->TSTR};
}

//---| RTC timestamp date register

static inline struct rtc_date rtc_get_timestamp_date(void)
{
        return (struct rtc_date) {.reg_val = RTC->TSDR};
}

//---| RTC time-stamp sub second register

//---| RTC calibration register

//---| RTC tamper & alternate function configuration register

//---| RTC alarm A sub second register

#endif // HW_RTC_H_