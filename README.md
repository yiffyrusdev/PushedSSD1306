# SSD1306 led driver library

## Description

PushedSSD1306 is a c++ library, mainly suited for led 128x64 displays driven by SSD1306 with I2C.

It uses display driver in page addressing mode, allowing you to write strings and chars to any position with any compatible font.

## Work in progress

- [x] Full custom font support
- [x] 128x64 displays
- [ ] 128x32 displays
- [x] Custom I2C library support
- [x] Char and C-string writing
- [ ] Check whether driver was connected with given addres or not
- [ ] Drawing functionality
  - [ ] Rectangles
  - [ ] Single Pixels
  - [ ] More comples geometrical shapes
  - [ ] Diagrams and graphics
  - [ ] Custom pictures (you can just define custom font wih picture)

## Requirements

1. C++ compiler with support of C++14 or later
2. Following header files in standard library:
  1. stdint.h (uintX_t type definitions)
  2. stddef.h (size_t definition)

## Compatibility

PushedSSD1306 uses I2C to communicate with display driver.

It has built-in support for TwoWire and TinyWireM communication libraries.

But you can adpot and use almost any other library if you want (see adoption examples).

## Motivation

There are many nice, shiny and beautiful led libraries for avr/esp32 etc.

But I wanted to use one library for all combinations of board+I2Clibrary+platform

And it was a bit painly to figure out that yet another library uses only Wire.h, or defines fonts in PROGMEM (if you want to use esp32), or does not allow to define custom fonts, or contains 5-6 different fonts that compiles into resulting binary file.

So, here it is. Library for SSD1306 independent from Arduino.h, that allows you to use const **or** PROGMEM fonts, any I2C library you like

## Examples

Check out the examples/ subfolder

## License

MIT
