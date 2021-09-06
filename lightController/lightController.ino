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

    // placeholder for command methods
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

  fillLEDsFromPalette(startIndex);

  FastLED.show();
  FastLED.delay(1000 / UPDATES_PER_SECOND);
}
