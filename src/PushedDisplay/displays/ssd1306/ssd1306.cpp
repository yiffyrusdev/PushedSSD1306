/* Copyright (C) 2023 Svyatoslav Pushkerav
This file is part of PushedSSD1306.
PushedSSD1306 is free software, distributed without any warranty.
You can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 3, or (at your option) any later version.
See the GNU General Public License v3.
<https://www.gnu.org/licenses/gpl-3.0.html> */

#include "PushedDisplay/displays/ssd1306/ssd1306_common.h"


#ifndef PUSSD1306_CONF_PAGES
  #define PUSSD1306_CONF_PAGES 8
#endif

bool PUSSD1306::begin(uint8_t i2c_address, pussd1306_resulution_e resolution)
{
  pui2c_begin();

  pui2c_transmit(i2c_address);
  pui2c_write(PUSSD_CTRL_CMD);
  pui2c_write(PUSSD_CMD_NOP);
  if (pui2c_end() != 0) return false;

  __i2c_address = i2c_address;

  switch (resolution){
    case Res128x32:
      __put_cmd(PUSSD_CMD_MULTIPLEX_RATIO);
      __put_cmd(PUSSD_DAT_MULTIPLEX_128X32);
      __put_cmd(PUSSD_CMD_COM_PINS);
      __put_cmd(PUSSD_DAT_COM_PINS_128X32);
      break;
    case Res128x64:
      __put_cmd(PUSSD_CMD_MULTIPLEX_RATIO);
      __put_cmd(PUSSD_DAT_MULTIPLEX_128X64);
      __put_cmd(PUSSD_CMD_COM_PINS);
      __put_cmd(PUSSD_DAT_COM_PINS_128X64);
      break;
  }
  

  reset();
  clear();

  return true;
}
void PUSSD1306::clear(void)
{
  for (uint8_t p = 0; p < PUSSD1306_CONF_PAGES; p++){
    setCursor(p, 0);
    for (uint8_t c = 0; c < 130; c++) writeByte(0x00);
  }
}

void PUSSD1306::reset(void)
{
  __put_cmd(PUSSD_CMD_DISPLAYOFF);

  __put_cmd(PUSSD_CMD_ADDRESS_MODE_PAGE);

  __put_cmd(PUSSD_CMD_CONTRAST);
  __put_cmd(PUSSD_BEGIN_CONTRAST);

  __put_cmd(PUSSD_BEGIN_SEG);
  __put_cmd(PUSSD_BEGIN_SCAN);
  __put_cmd(PUSSD_BEGIN_POL);

  __put_cmd(PUSSD_CMD_OSC_DIV);
  __put_cmd(PUSSD_BEGIN_OSC_DIV);

  __put_cmd(PUSSD_CMD_PRECHARGE);
  __put_cmd(PUSSD_BEGIN_PRECHARGE);

  __put_cmd(PUSSD_CMD_VCOMH);
  __put_cmd(PUSSD_BEGIN_VCOMH);

  __put_cmd(PUSSD_CMD_DISPLAYON);

  clear();
  setCursor(0, 0);
}

void PUSSD1306::setCursor(uint8_t page, uint8_t col)
{
  __put_cmd(PUSSD_CMD_SET_PAGE | page);
  __put_cmd(PUSSD_CMD_SET_LOW_COL | ((col & 0b00001111)));
  __put_cmd(PUSSD_CMD_SET_HIGH_COL | (col & 0b11110000) >> 4);

  __cache_col = col;
  __cache_page = page;
}

void PUSSD1306::test(void)
{
  uint8_t label00[] = {0xf2,0x95,0xf0,0x0,0xf2,0x91,0xf2};

  for(int x=0; x<8; x++){
    for(int y=0; y<128; y++){
      setCursor(x, y);
      writeByte(0xff);
      }  
  }
  for(int x=0; x<8; x++){
    for(int y=0; y<128; y++){
      setCursor(x, y);
      writeByte(0x00);
      }  
  }

  clear();

  setCursor(0, 0);
  __put_dat_seq(7, label00);

}
void PUSSD1306::writeByte(uint8_t b)
{
  __put_dat(b);
}

void PUSSD1306::__put_cmd(uint8_t cmdbyte)
{
  pui2c_transmit(__i2c_address);
  pui2c_write(PUSSD_CTRL_CMD);
  pui2c_write(cmdbyte);
  pui2c_end();
}

void PUSSD1306::__put_dat(uint8_t datbyte)
{
  pui2c_transmit(__i2c_address);
  pui2c_write(PUSSD_CTRL_DAT);
  pui2c_write(datbyte);
  pui2c_end();
}


void PUSSD1306::__put_dat_seq(uint8_t len, const uint8_t* datbytes){
  for (uint8_t ibyte = 0; ibyte < len; ibyte++)
    __put_dat(datbytes[ibyte]);
}