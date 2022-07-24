#ifndef LEDS_H
#define LEDS_H

#include <FastLED.h>
// #include "ArduinoSTL.h"
// #include "map"

#define LED_PIN     7
#define NUM_LEDS    60
#define BRIGHT      64
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define UPDATES_PER_SECOND 100

extern CRGB ledStrip[NUM_LEDS];
extern int8_t paletteIndex;
extern int8_t paletteSize;
extern CRGBPalette16 currentPalette;
extern TBlendType currentBlending;

extern CRGBPalette16 redWhiteBluePalette;
extern const PROGMEM TProgmemPalette16 redWhiteBluePalette_p;

// extern std::map<char*, CRGBPalette16> paletteMap;

extern CRGBPalette16 palettes[];
extern TBlendType blends[];

void fillLEDsFromPalette(uint8_t colorIndex);
void cyclePalette(char data);

#endif
