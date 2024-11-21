/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2024 Lars Görner */

#ifndef HW_LTC2942_H_
#define HW_LTC2942_H_

#define LTC2942_I2C_ADDR        0x64

#define LTC2942_REG_STAT        0x00 /**< Status */
#define LTC2942_REG_CTL         0x01 /**< Control */
#define LTC2942_REG_AC_MSB      0x02 /**< Accumulated charge MSB */
#define LTC2942_REG_AC_LSB      0x03 /**< Accumulated charge LSB */
#define LTC2942_REG_CTH_MSB     0x04 /**< Charge threshold high MSB */
#define LTC2942_REG_CTH_LSB     0x05 /**< Charge threshold high LSB */
#define LTC2942_REG_CTL_MSB     0x06 /**< Charge threshold low MSB */
#define LTC2942_REG_CTL_LSB     0x07 /**< Charge threshold low LSB */
#define LTC2942_REG_VOL_MSB     0x08 /**< Voltage MSB */
#define LTC2942_REG_VOL_LSB     0x09 /**< Voltage LSB */
#define LTC2942_REG_VT_HI       0x0A /**< Voltage theshold high */
#define LTC2942_REG_VT_LO       0x0B /**< Voltage theshold low */
#define LTC2942_REG_TEMP_MSB    0x0C /**< Temperature MSB */
#define LTC2942_REG_TEMP_LSB    0x0D /**< Temperature LSB */
#define LTC2942_REG_TT_HI       0x0E /**< Temperature threshold high */
#define LTC2942_REG_TT_LO       0x0F /**< Temperature threshold low */

#endif // HW_LTC2942_H_