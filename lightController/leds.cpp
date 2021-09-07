#include "leds.h"

CRGB leds[NUM_LEDS];
int8_t paletteIndex = 0;
int8_t paletteSize = 8;
CRGBPalette16 currentPalette;
TBlendType currentBlending;

std::map<char*, CRGBPalette16> paletteMap {
  { "RainbowColors_p",       RainbowColors_p },
  { "RainbowStripeColors_p", RainbowStripeColors_p },
  { "OceanColors_p",         OceanColors_p },
  { "CloudColors_p",         CloudColors_p },
  { "LavaColors_p",          LavaColors_p },
  { "ForestColors_p",        ForestColors_p },
  { "PartyColors_p",         PartyColors_p },
  { "redWhiteBluePalette_p", redWhiteBluePalette_p }
};

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
    leds[i] =
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
void blackAndWhiteStripes() {
  // black out all 16 palette entries
  fill_solid(currentPalette, 16, CRGB::Black);

  // set every fourth one to white
  currentPalette[0] = CRGB::White;
  currentPalette[4] = CRGB::White;
  currentPalette[8] = CRGB::White;
  currentPalette[12] = CRGB::White;
}

void setupPurpleAndGreenPalette() {
  CRGB purple = CHSV(HUE_PURPLE, 255, 255);
  CRGB green = CHSV(HUE_GREEN, 255, 255);
  CRGB black = CRGB::Black;

  currentPalette = CRGBPalette16(
    green,  green,  black,  black,
    purple, purple, black,  black,
    green,  green,  black,  black,
    purple, purple, black,  black
  );
}

// Example static color palette - 64 bytes of flash
const TProgmemPalette16 redWhiteBluePalette_p PROGMEM = {
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
