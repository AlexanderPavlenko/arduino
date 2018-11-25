#include <FastLED.h>  // https://github.com/FastLED/FastLED
#include <WS2812FX.h> // https://github.com/kitesurfer1404/WS2812FX

#define LED_TYPE    WS2811
#define LED_PIN     8
#define LED_COUNT   300
#define COLOR_ORDER GRB
#define BRIGHTNESS  255

CRGB leds[LED_COUNT];
CRGBPalette16 palette;
TBlendType    blending;

WS2812FX ws2812fx = WS2812FX(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  delay(500); // "power-up safety"
  setupFastLED();
//  setupWS2812FX();
}

void loop() {
//  FastLED, pick one:
//  morph();
  stream();
//  all_at_once();
  
//  or WS2812FX:
//  ws2812fx.service();
}

void setupFastLED() {
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, LED_COUNT).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  palette = RainbowColors_p;
//  palette = PartyColors_p;
  blending = LINEARBLEND;
}

void setupWS2812FX() {
  ws2812fx.init();
  ws2812fx.setBrightness(BRIGHTNESS);

//  A)
  ws2812fx.setMode(FX_MODE_FIREWORKS_RANDOM);
  ws2812fx.setSpeed(50000);

//  B)
//  ws2812fx.setSegment(0, 0,   99,  FX_MODE_LARSON_SCANNER, RED,   20000, false);
//  ws2812fx.setSegment(1, 100, 199, FX_MODE_LARSON_SCANNER, GREEN, 10000, false);
//  ws2812fx.setSegment(2, 200, 299, FX_MODE_LARSON_SCANNER, BLUE,  5000, false);
  
  ws2812fx.start();
}


#define MORPH_SEAMLESS 10
#define MORPH_DELAY 55
void morph() {
  static uint8_t colorIndex = 0;

  for(int mod = 0; mod < MORPH_SEAMLESS; mod++) {
    for(int i = 0; i < LED_COUNT; i++) {
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

  for(int i = 0; i < LED_COUNT; i++) {
    leds[i] = ColorFromPalette(palette, i - offset, BRIGHTNESS, blending);
  }
  FastLED.show();
  delay(STREAM_DELAY);

  offset++;
}

void all_at_once() {
  for(int i = 0; i < LED_COUNT; i++) {
    leds[i] = ColorFromPalette(palette, i, BRIGHTNESS, blending);
  }
  FastLED.show();
  exit(0);
}
