/* SPDX-License-Identifier: MIT */
/* Copyright (c) 2024 Lars Görner */

#ifndef HW_SSD1677_H_
#define HW_SSD1677_H_

#define SSD1677_CMD_DOC         0x01 /**< Driver Output Control */
#define SSD1677_CMD_GDVC        0x03 /**< Gate Driving Voltage Control */
#define SSD1677_CMD_SDVC        0x04 /**< Source Driving Voltage Control */
#define SSD1677_CMD_ICS         0x08 /**< Initial Code Setting OTP Program */
#define SSD1677_CMD_ICS_WR      0x09 /**< Write Register for Initial Code Setting */
#define SSD1677_CMD_ICS_RD      0x0A /**< Read Register for Initial Code Setting */
#define SSD1677_CMD_BSSC        0x0C /**< Booster Soft-Start Control */
#define SSD1677_CMD_DSM         0x10 /**< Deep Sleep Mode */
#define SSD1677_CMD_DEMS        0x11 /**< Data Entry Mode Setting */
#define SSD1677_CMD_SWR         0x12 /**< Software Reset */
#define SSD1677_CMD_HVRD        0x14 /**< HV Ready Detection */
#define SSD1677_CMD_VCID        0x15 /**< VCI Detection */
#define SSD1677_CMD_TSC         0x18 /**< Temperature Sensor Control */
#define SSD1677_CMD_TSC_WR      0x1A /**< Write Register for Temperature Sensor */
#define SSD1677_CMD_TSC_RD      0x1B /**< Read Register for Temperature Sensor */
#define SSD1677_CMD_TSC_WR_EXT  0x1C /**< Write Register for external Temperature Sensor */
#define SSD1677_CMD_MA          0x20 /**< Master Activation */
#define SSD1677_CMD_DUC1        0x21 /**< Display Update Control 1 */
#define SSD1677_CMD_DUC2        0x22 /**< Display Update Control 2 */
#define SSD1677_CMD_RAM_BW_WR   0x24 /**< Write RAM (B/W) */
#define SSD1677_CMD_RAM_DITH_WR 0x25 /**< Write RAM (Dithering) */
#define SSD1677_CMD_RAM_RED_WR  0x26 /**< Write RAM (Red) */
#define SSD1677_CMD_RAM_RD      0x27 /**< Read RAM */
#define SSD1677_CMD_VCOM_SENSE  0x28 /**< VCOM Sense */
#define SSD1677_CMD_VCOM_SD     0x29 /**< VCOM Sense Duration */
#define SSD1677_CMD_PVO         0x2A /**< Program VCOM OTP */
#define SSD1677_CMD_VC_WR       0x2B /**< Write Register for VCOM Control */
#define SDD1677_CMD_VCOM        0x2C /**< Write VCOM Register */
#define SSD1677_CMD_DO_RD       0x2D /**< OTP Register Read for Display Option */
#define SSD1677_CMD_UID         0x2E /**< User ID Read */
#define SSD1677_CMD_SB          0x2F /**< Status Bit Read */
#define SSD1677_CMD_PWO         0x30 /**< Program WS OTP */
#define SSD1677_CMD_LWO         0x31 /**< Load WS OTP */
#define SDD1677_CMD_LUT_WR      0x32 /**< Write LUT Register */
#define SSD1677_CMD_CRC         0x34 /**< CRC Calculation */
#define SSD1677_CMD_CRC_S       0x35 /**< CRC Status Read */
#define SSD1677_CMD_POS         0x36 /**< Program OTP Selection */
#define SSD1677_CMD_DO_WR       0x37 /**< Write Register for Display Option */
#define SSD1677_CMD_UID_WR      0x38 /**< Write Register for User ID */
#define SSD1677_CMD_OPM         0x39 /**< OTP Program Mode */
#define SSD1677_CMD_BWC         0x3C /**< Border Waveform Control */
#define SSD1677_CMD_RRO         0x41 /**< Read RAM Option */
#define SSD1677_CMD_RAM_X       0x44 /**< Set RAM X-Address Start/End Position */
#define SSD1677_CMD_RAM_Y       0x45 /**< Set RAM Y-Address Start/End Position */
#define SSD1677_CMD_AWRR        0x46 /**< Auto Write RED RAM for Regular Pattern */
#define SSD1677_CMD_AWBWR       0x47 /**< Auto Write B/W RAM for Regular Pattern */
#define SSD1677_CMD_DE          0x4D /**< Dithering Engine Start/Stop */
#define SSD1677_CMD_RAM_X_C     0x4E /**< Set RAM X-Address Counter */
#define SSD1677_CMD_RAM_Y_C     0x4F /**< Set RAM Y-Address Counter */
#define SSD1677_CMD_NOP         0x7F /**< NOP */

#endif // HW_SSD1677_H_