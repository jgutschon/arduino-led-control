#include <FastLED.h>

#define LED_PIN     7
#define NUM_LEDS    30
#define BRIGHT  64
#define LED_TYPE    WS2812B
#define COLOR_ORDER GRB
#define UPDATES_PER_SECOND 100
CRGB leds[NUM_LEDS];

int8_t paletteIndex = 0;
int8_t paletteSize = 8;
CRGBPalette16 currentPalette;
TBlendType currentBlending;

extern CRGBPalette16 myRedWhiteBluePalette;
extern const TProgmemPalette16 redWhiteBluePalette_p PROGMEM;

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

// messaging
const uint8_t bufSize = 128;
char msg[bufSize];
boolean newData = false;
const char start = '`';
const char end = '~';

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

void lightSwitch(char* setting) {
  int brightness;
  if (strstr(setting, "on")) {
    brightness = BRIGHT;
  } else if (strstr(setting, "off")) {
    brightness = 0;
  }

  FastLED.setBrightness(brightness);
}

// void setPalette(char* setting) {
//   currentPalette = 
// }

void readSerial() {
  static boolean recvInProgress = false;
  static uint8_t ndx = 0;
  
  char rc;

  while (Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if (recvInProgress == true) {
      if (rc != end) {
        msg[ndx] = rc;
        ndx++;
        if (ndx >= bufSize) {
          ndx = bufSize - 1;
        }
      } else {
        msg[ndx] = '\0';  // terminate the string
        recvInProgress = false;
        ndx = 0;
        newData = true;
      }
    }

    else if (rc == start) {
      recvInProgress = true;
    }
  }
}

void printSerial() {
  if (newData) {
    Serial.println(msg);
    newData = false;
  }
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
