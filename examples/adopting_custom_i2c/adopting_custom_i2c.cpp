// Nice to meet you!

/* Include required conditions:
1. Adopting definitios for I2C library
2. avr/pgmspace (if you want to use PROGMEM fonts)
3. Display library and fonts
*/

// The first thing is font. You can choose one form PushedDisplayFonts library or write your custom
// There are two options for each font: const (suitable for esp32) and progmem (suitable for avr or if you want to use RAM)

// Lets use my font
// If you want to use PROGMEM fonts:
#include <avr/pgmspace.h>
#include <PushedDisplay/fonts/font_w5h8_avrpgm.h>

// If you want to use const font
//#include <PushedDisplay/fonts/font_w5h8_const.h>

// Then you have to decide which I2C library you want to use
// #include <Wire.h> // Basic for many boards
//#include <TinyWireM.h>  // Alternative for attiny
// Lets adopt custom I2C library
#define PUI2C_ADOPT
#include "MyAwesomeI2C.h"
void pui2c_begin(){
  // Startup and load actions for your I2C library
  MyAwesomeI2C.begin();
}
void pui2c_transmit(uint8_t addr){
  // Actions called every time BEFORE I2C transmission, when we ask slave to receive bytes
  MyAwesomeI2c.beginTransmission(addr);
}
uint8_t pui2c_request(uint8_t addr, uint8_t wrbytes){
  // Actions called every time BEFORE I2C transmission, when we ask slave to send bytes
  // Fair return, that will be compatible with Wire.h returnvalues is highly recommended
  uint8_t bits = MyAwesomeI2c.requestFrom(addr, wrbytes);
  // Lets imagine thatour library return amount of bits instead of amount of bytes
  return bits/8;
}
size_t pui2c_write(uint8_t wrbyte){
  // Actions called every time to WRITE bytes to slave
  // Fair return, that will be compatible with Wire.h retirnvalues is highly recommended
  return MyAwesomeI2c.write(wrbyte);
}
int pui2c_read(){
  // Actions calles every time to READ bytes from slave
  // Fair return, that will be compatible with Wire.h returnvalues is highly recommended
  return MyAwesomeI2C.read();
}
uint8_t pui2c_end(){
  // Actions called every time AFTER I2C transmittion
  // Fair return, that will be compatible with Wire.h returncodes is highly recommended
  uint8_t returncode = Wire.endTransmission();
  // Lets imagine that our library uses different returncodes:
  // 1 - success
  // 2 - data too long
  // 3 - NACK on address
  // 4 - NACK on data
  // 5 - other error
  // 6 - timeout
  switch (returncode){
    case 1:
      return 0;
    case 2:
      return 1;
    case 3:
      return 2;
    case 4:
      return 3;
    case 5:
      return 4;
    case 6:
      return 5;
    default:
      return 4;
  }
}

#include <PushedDisplay/displays/ssd1306/ssd1306.h>

// Now we are ready to go

PUSSD1306 lcd;

void main(){
  lcd.begin(0x3C);

  lcd.clear();

  lcd.setCursor(0, 2);
  lcd.writeByte(0x87);

  lcd.setCursor(1, 2);
  // writeChar is template function. Default tparams are set to suite 5x8 font
  // But if you want to use other font, you will have to set them (see the docs)
  // First tparam is amount of bytes per symbol
  // Second tparam is amount of pages used by symbol
  lcd.writeChar<>(pu_font_w5h8_avrpgm, '@');

  lcd.setCursor(2, 2);
  // writeString is also template function.
  // Same logic as for writeChar
  lcd.writeString<>(pu_font_w5h8_avrpgm, "Hello ");
}