#include "leds.h"

CRGB ledStrip[NUM_LEDS];
int8_t paletteIndex = 0;
int8_t paletteSize = 8;
CRGBPalette16 currentPalette;
TBlendType currentBlending;

// std::map<char*, CRGBPalette16> paletteMap {
//   { "RainbowColors_p",       RainbowColors_p },
//   { "RainbowStripeColors_p", RainbowStripeColors_p },
//   { "OceanColors_p",         OceanColors_p },
//   { "CloudColors_p",         CloudColors_p },
//   { "LavaColors_p",          LavaColors_p },
//   { "ForestColors_p",        ForestColors_p },
//   { "PartyColors_p",         PartyColors_p },
//   { "redWhiteBluePalette_p", redWhiteBluePalette_p }
// };

CRGBPalette16 palettes[] = {
  RainbowColors_p,
  RainbowStripeColors_p,
  OceanColors_p,
  CloudColors_p,
  LavaColors_p,
  ForestColors_p,
  PartyColors_p,
  redWhiteBluePalette_p,
};

TBlendType blends[] = {
  LINEARBLEND,
  NOBLEND,
  LINEARBLEND,
  LINEARBLEND,
  LINEARBLEND,
  LINEARBLEND,
  NOBLEND,
  LINEARBLEND,
};

// control methods
void fillLEDsFromPalette(uint8_t colorIndex) {
  uint8_t bright = 255;

  for (int i = 0; i < NUM_LEDS; i++) {
    ledStrip[i] =
        ColorFromPalette(currentPalette, colorIndex, bright, currentBlending);
    colorIndex += 3;
  }
}

void cyclePalette(char data) {
  if (data == 'n')
    paletteIndex++;
  else if (data == 'p')
    paletteIndex--;

  // keep indexing in array bounds
  if (paletteIndex < 0)
    paletteIndex = paletteSize - 1;
  if (paletteIndex > paletteSize - 1)
    paletteIndex = 0;

  currentPalette = palettes[paletteIndex];
  currentBlending = blends[paletteIndex];
}

// Custom Palettes
// Example static color palette - 64 bytes of flash
const TProgmemPalette16 redWhiteBluePalette_p = {
  CRGB::Red,
  CRGB::Gray,
  CRGB::Blue,
  CRGB::Black,
  
  CRGB::Red,
  CRGB::Gray,
  CRGB::Blue,
  CRGB::Black,
  
  CRGB::Red,
  CRGB::Red,
  CRGB::Gray,
  CRGB::Gray,

  CRGB::Blue,
  CRGB::Blue,
  CRGB::Black,
  CRGB::Black
};
