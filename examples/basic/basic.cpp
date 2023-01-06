// Nice to meet you!

/* Include required conditions:
1. I2C library (Wire.h or TinyWireM.h)
2. avr/pgmspace (if you want to use PROGMEM fonts)
3. Display library and fonts
*/

// The first thing is font. You can choose one form PushedDisplayFonts library or write your custom
// There are two options for each font: const (suitable for esp32) and progmem (suitable for avr or if you want to use RAM)

// Lets use my font
// If you want to use PROGMEM fonts:
#include <avr/pgmspace.h>
#include <PushedDisplay/fonts/font_w5h8_avrpgm.h>
#include <PushedDisplay/fonts/font_w9h16_avrpgm.h>

// If you want to use const font
//#include <PushedDisplay/fonts/font_w5h8_const.h>

// Then you have to decide which I2C library you want to use
#include <Wire.h> // Basic for many boards
//#include <TinyWireM.h>  // Alternative for attiny
// You may also use any other I2C library, but then you'll have to "adopt" it (see according example)
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
  lcd.writeChar<9, 2>(pu_font_w9h16_avrpgm, '$');

  lcd.setCursor(2, 2);
  // writeString is also template function.
  // Same logic as for writeChar
  lcd.writeString<>(pu_font_w5h8_avrpgm, "Hello ");
  lcd.writeString<9, 2>(pu_font_w9h16_avrpgm, "OOPS");
}