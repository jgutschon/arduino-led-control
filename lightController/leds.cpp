#include "leds.h"

CRGB leds[NUM_LEDS];
int8_t paletteIndex = 0;
int8_t paletteSize = 8;
CRGBPalette16 currentPalette;
TBlendType currentBlending;
