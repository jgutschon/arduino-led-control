#include "commands.h"

void lightSwitch(char* setting) {
  uint8_t brightness;
  if (strstr(setting, "on")) {
    brightness = BRIGHT;
  } else if (strstr(setting, "off")) {
    brightness = 0;
  }

  FastLED.setBrightness(brightness);
}

void setPalette(char* palette) {
  // placeholder to retain original functionality
  if (strstr(palette, "next")) {
    cyclePalette('n');
  } else if (strstr(palette, "prev")) {
    cyclePalette('p');
  } else {
    // currentPalette = paletteMap[palette];
  }
}

// TODO: other command implementations
// void setBlend(char* blend);
// void setBrightness(char* brightness);
// void setSpeed(char* speed);
