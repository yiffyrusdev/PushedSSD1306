/* Copyright (C) 2023 Svyatoslav Pushkerav
This file is part of PushedSSD1306.
This particular file is provided to you for any use you see fit.
If used as part of the project within which it is published, see the project license.
However, this particular file may be used independently by you in full freedom of action without restrictions.
The only condition is that you will credit me in modified or copied version of this file.
If this file is modified, please also add a note that the file has been modified.
If you include the contents of this file in another project, please credit me to your new file.
*/

#ifndef PUSSD_CMD_h

#define PUSSD_CTRL_CMD 0x80
#define PUSSD_CTRL_DAT 0xC0
#define PUSSD_CTRL_DAT_SEQ 0x40

#define PUSSD_CMD_NOP 0xE3
#define PUSSD_CMD_ENTIRE_ON_RAM 0xA4
#define PUSSD_CMD_ENTIRE_ON_NORAM 0xA5
#define PUSSD_CMD_DISPLAYOFF 0xAE
#define PUSSD_CMD_DISPLAYON 0xAF
#define PUSSD_CMD_CONTRAST 0x81 // double-byte command. Next is contrast byte 0-255
#define PUSSD_CMD_POL_NORMAL 0xA6 // bit 1 switched pixel ON, 0 to OFF
#define PUSSD_CMD_POL_INVERSE 0xA7 // bit 1 switches pixel OFF, 0 to ON
#define PUSSD_CMD_ADDRESS_MODE_PAGE 0x02 // PAGE addressing mode
#define PUSSD_CMD_MULTIPLEX_RATIO 0xA8 // double-byte command. Next is duty
#define PUSSD_CMD_SCAN_NORMAL 0xC0 // page order
#define PUSSD_CMD_SCAN_REMAP 0xC8 // page order
#define PUSSD_CMD_SEG_NORMAL 0xA0 // column order
#define PUSSD_CMD_SEG_REMAP 0xA1 // column order
#define PUSSD_CMD_OSC_DIV 0xD5 // double-byte command. Next is osc division
#define PUSSD_CMD_PRECHARGE 0xD9 // double-byte command. Next is period
#define PUSSD_CMD_COM_PINS 0xDA // double-byte command. Next is config (see datasheet)
#define PUSSD_CMD_VCOMH 0xDB // double-byte command. Next is deselect level

#define PUSSD_CMD_SET_PAGE 0xB0 // incomplete byte. Needs 3 bits at the end (0b000-0b111 -- page0-page7)
#define PUSSD_CMD_SET_LOW_COL 0x00 //incomplete byte. Needs 4 bits at the end(0b0000-0b1111)
#define PUSSD_CMD_SET_HIGH_COL 0x10 // incomplete byte. Needs 4 bits at the end (0b0000-0b1111)

#define PUSSD_DAT_MULTIPLEX_128X64 0x3F
#define PUSSD_DAT_MULTIPLEX_128X32 0x1F

#define PUSSD_DAT_COM_PINS_128X64 0x12
#define PUSSD_DAT_COM_PINS_128X32 0x02

#ifndef PUSSD_BEGIN_SEG
  #define PUSSD_BEGIN_SEG PUSSD_CMD_SEG_REMAP
#endif

#ifndef PUSSD_BEGIN_SCAN
  #define PUSSD_BEGIN_SCAN PUSSD_CMD_SCAN_REMAP
#endif

#ifndef PUSSD_BEGIN_POL
  #define PUSSD_BEGIN_POL PUSSD_CMD_POL_NORMAL
#endif

#ifndef PUSSD_BEGIN_OSC_DIV
  #define PUSSD_BEGIN_OSC_DIV 0x80
#endif

#ifndef PUSSD_BEGIN_PRECHARGE
  #define PUSSD_BEGIN_PRECHARGE 0xF1
#endif

#ifndef PUSSD_BEGIN_CONTRAST
  #define PUSSD_BEGIN_CONTRAST 0x55
#endif

#ifndef PUSSD_BEGIN_VCOMH
  #define PUSSD_BEGIN_VCOMH 0x20
#endif

#endif