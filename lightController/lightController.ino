#include <FastLED.h>
#include "leds.h"
#include "commands.h"
#include "message.h"

void setup() {
  Serial.begin(9600);
  while(!Serial) continue;

  delay(2000);  // power-up safety delay
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS)
      .setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHT);

  currentPalette = RainbowColors_p;
  currentBlending = LINEARBLEND;
}

void loop() {
  readSerial();

  if (newData) {
    char* channel = strtok(msg, "/");
    char* setting = strtok(NULL, "/");

    Serial.print("channel: ");
    Serial.println(channel);
    Serial.print("setting: ");
    Serial.println(setting);

    if (strstr(channel, "power")) {
      lightSwitch(setting);
    } else if (strstr(channel, "palette")) {
      Serial.println("palette");
    } else if (strstr(channel, "blend")) {
      Serial.println("blend");
    } else if (strstr(channel, "brightness")) {
      Serial.println("brightness");
    } else if (strstr(channel, "speed")) {
      Serial.println("speed");
    }

    newData = false;
  }

  static uint8_t startIndex = 0;
  startIndex++;  // motion speed

  fillLEDsFromPaletteColors(startIndex);

  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);
}

void fillLEDsFromPaletteColors(uint8_t colorIndex) {
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
