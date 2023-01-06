/* Copyright (C) 2023 Svyatoslav Pushkerav
This file is part of PushedSSD1306.
PushedSSD1306 is free software, distributed without any warranty.
You can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3, or (at your option) any later version.
See the GNU General Public License v3.
<https://www.gnu.org/licenses/gpl-3.0.html> */

#ifndef PUSSD1306_COMMON_h
#define PUSSD1306_COMMON_h

#include <string.h>
#include <stdint.h>
#include <stddef.h>
#include "PushedDisplay/displays/ssd1306/ssd1306_cmd.h"
#include "PushedDisplay/displays/ssd1306/ssd1306_sharedconfigurable.h"

enum pussd1306_resulution_e{
  Res128x64,
  Res128x32
};


class PUSSD1306{
  public:
    PUSSD1306(){}
    /// @brief Connect to slave SSD1306 device.
    /// @param i2c_address byte address of device
    /// @return True if device returnc ACK, False otherwise
    bool begin(uint8_t i2c_address = 0x3C, pussd1306_resulution_e resulution = Res128x64);
    /// @brief Clear display.
    void clear(void);
    /// @brief Reset display settings.
    void reset(void);
    /// @brief Set cursor to specified position.
    /// @param page Page number
    /// @param col Column in page
    void setCursor(uint8_t page, uint8_t col);

    /// Run simple display tests.
    /// Test includes: sequential pixel enable/disable, writing at 0page,0col
    void test(void);

    /// @brief Write ASCII char to current cursor position
    /// @tparam FontWidth Bytes per symbol. Normally stated in font name.
    /// @tparam FontHeight Pages per symbol
    /// @param font font to use
    /// @param c ASCII char to write
    template<uint8_t FontWidth=5, uint8_t FontHeight=1>
    void writeChar(const unsigned char font[][FontHeight][FontWidth], char c, uint8_t char_spacing=1)
    {
      uint8_t symbolbuffer[FontWidth];
      c -= 32;
      if (c > 127) c = 0;
      switch (FontHeight){
        case 1:
          pu_read_font_page(symbolbuffer, font, c, 0);
          __put_dat_seq(FontWidth, symbolbuffer);
          break;
        default:
          {
            uint8_t origin_page = __cache_page;
            for (uint8_t ipage = 0; ipage < FontHeight; ipage++){
                pu_read_font_page(symbolbuffer, font, c, ipage);
                __put_dat_seq(FontWidth, symbolbuffer);
              for (uint8_t sp = 0; sp < char_spacing; sp++) writeByte(0x00);
              setCursor(__cache_page+1, __cache_col);
            }
            setCursor(origin_page, __cache_col+FontWidth+char_spacing);
          }
          break;
      }
    }

    /// @brief Write byte to current cursor position
    /// @param b  Byte
    void writeByte(uint8_t b);

    /// @brief Write string from current cursor position
    /// @tparam FontWidth Bytes per symbol. Normally stated in font name.
    /// @tparam FontHeight Pages per symbol
    /// @param str c-string to write
    /// @param char_spacing empty cols between shars in string
    template<uint8_t FontWidth=5, uint8_t FontHeight=1>
    void writeString(const uint8_t font[][FontHeight][FontWidth], const char* text, uint8_t char_spacing=1)
    {
      for (size_t c = 0; c < strlen(text); c++){
        if (text[c] == '\0') break;
        writeChar<FontWidth, FontHeight>(font, text[c], char_spacing);
      } 
    }
  private:
    uint8_t __i2c_address;
    uint8_t __cache_col;  // Last col set by setCursor
    uint8_t __cache_page; // Last page set by setCursor

    /// @brief Write command byte to ssd
    /// @param cmdbyte command byte
    void __put_cmd(uint8_t cmdbyte);
    /// @brief Write data byte to ssd
    /// @param datbyte data byte
    void __put_dat(uint8_t datbyte);
    /**
     * Send many data bytes at once.
     * Use only for data.
     * Do not send more than 16 bytes as once. Bigger sequences may be trimmed by display driver.
     * @param len length of byte sequence
     * @param datbytes bytes to send
    */
    void __put_dat_seq(uint8_t len, const uint8_t* datbytes);
};


#endif
