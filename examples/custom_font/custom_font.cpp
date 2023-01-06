// Nice to meet you!

/* Include required conditions:
1. I2C library (Wire.h or TinyWireM.h)
2. avr/pgmspace (if you want to use PROGMEM fonts)
3. Display library and fonts
*/

// The first thing is font. You can choose one form PushedDisplayFonts library or write your custom
// There are two options for each font: const (suitable for esp32) and progmem (suitable for avr or if you want to use RAM)

/* Important notes about fonts:
1. Font must define all ASCII symbols from 32 (' ') till (at least) the last one you are going to use
2. The last allowed symbol to define is ASCII 127 (EMPTY) Any symbols with codes bigger will be represented as ' '
3. Pages comes in order top->bottom
4. Bytes in page comes in order top->bottom
*/


// Lets our custom defined font
// If you want to use PROGMEM fonts:
#include <avr/pgmspace.h>
#define BYTES_PER_SYMBOL 9
#define PAGES_PER_SYMBOL 2
const uint8_t my_awesome_font[][PAGES_PER_SYMBOL][BYTES_PER_SYMBOL] PROGMEM = {
  // 32 -- ' '
  {{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0} // first page
  ,{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0}}, // second page
  // 33 -- '!'
  {{0x0,0x0,0x0,0xfc,0xfe,0xfe,0xfc,0x0,0x0} // first page
  ,{0x0,0x0,0x0,0x0,0xdf,0xdf,0x0,0x0,0x0}}, // second page
  // 34 -- '"'
  {{0x0,0x0,0x3e,0x3e,0x0,0x3e,0x3e,0x0,0x0} // first page
  ,{0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0}},  // second page
  // 35 -- '#'
  {{0x30,0x30,0xfe,0xfe,0x30,0x30,0xfe,0xfe,0x30}  // first page
,{0x18,0x18,0xff,0xff,0x18,0x18,0xff,0xff,0x18}},  // second page
};
// I'm sure that the last symbol I want to use is '#', so i can define only symbols from 32 till 25

// If you want to use const font
// Just define it as const uint8_t font[][][] = {...};

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
  lcd.writeChar<9, 2>(my_awesome_font, '!');

  lcd.setCursor(2, 2);
  // writeString is also template function.
  // Same logic as for writeChar
  lcd.writeString<9, 2>(my_awesome_font, "##!!##");
}