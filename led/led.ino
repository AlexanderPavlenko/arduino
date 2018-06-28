#include <FastLED.h>

#define LED_TYPE    WS2811
#define LED_PIN     8
#define COLOR_ORDER GRB
#define NUM_LEDS    300
#define BRIGHTNESS  255
#define UPDATES_PER_SECOND 18.8
#define SEAMLESS 10

CRGB leds[NUM_LEDS];
CRGBPalette16 currentPalette;
TBlendType    currentBlending;

void setup() {
  delay(500); // "power-up safety"
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  // currentPalette = RainbowColors_p;
  currentPalette = PartyColors_p;
  currentBlending = LINEARBLEND;
}


void loop() {
  morph();
  // all_at_once();
}

void morph() {
  static uint8_t colorIndex = 0;
  static uint8_t brightness = 255;

  for(int mod = 0; mod < SEAMLESS; mod++) {
    for(int i = 0; i < NUM_LEDS; i++) {
      if(i % SEAMLESS == mod) {
        leds[i] = ColorFromPalette(currentPalette, colorIndex, brightness, currentBlending);
      }
    }
    FastLED.show();
    delay(1000 / UPDATES_PER_SECOND);
  }

  colorIndex = colorIndex + 1;
}

void all_at_once() {
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette(currentPalette, i, 255, currentBlending);
  }
  FastLED.show();
  exit(0);
}
