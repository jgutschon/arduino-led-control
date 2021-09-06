#include "commands.h"

void lightSwitch(char* setting) {
  int brightness;
  if (strstr(setting, "on")) {
    brightness = BRIGHT;
  } else if (strstr(setting, "off")) {
    brightness = 0;
  }

  FastLED.setBrightness(brightness);
}
