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

// TODO: other command implementations
// void setPalette(char* palette);
// void setBlend(char* blend);
// void setBrightness(char* brightness);
// void setSpeed(char* speed);
