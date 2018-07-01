#include <FastLED.h>

#define LED_TYPE    WS2811
#define LED_PIN     8
#define COLOR_ORDER GRB
#define NUM_LEDS    300
#define BRIGHTNESS  255

CRGB leds[NUM_LEDS];
CRGBPalette16 palette;
TBlendType    blending;

void setup() {
  delay(500); // "power-up safety"
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  // palette = RainbowColors_p;
  palette = PartyColors_p;
  blending = LINEARBLEND;
}

void loop() {
  morph();
  // stream();
  // all_at_once();
}

#define MORPH_SEAMLESS 10
#define MORPH_DELAY 55
void morph() {
  static uint8_t colorIndex = 0;

  for(int mod = 0; mod < MORPH_SEAMLESS; mod++) {
    for(int i = 0; i < NUM_LEDS; i++) {
      if(i % MORPH_SEAMLESS == mod) {
        leds[i] = ColorFromPalette(palette, colorIndex, BRIGHTNESS, blending);
      }
    }
    FastLED.show();
    delay(MORPH_DELAY);
  }

  colorIndex++;
}

#define STREAM_DELAY 25
void stream(){
  static uint8_t offset = 0;

  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette(palette, i - offset, BRIGHTNESS, blending);
  }
  FastLED.show();
  delay(STREAM_DELAY);

  offset++;
}

void all_at_once() {
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = ColorFromPalette(palette, i, BRIGHTNESS, blending);
  }
  FastLED.show();
  exit(0);
}
