#include <Arduino.h>
#include <FastLED.h>

#define TOTAL_NUM_LEDS 300
#define DATA_PIN 6

CRGB leds[TOTAL_NUM_LEDS];
uint8_t hue = 0;

void setup() { 
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, TOTAL_NUM_LEDS);
  for (size_t i = 0; i < TOTAL_NUM_LEDS; i++) {
    leds[i] = CRGB(0, 0, 0);
  }
}

void loop() {
  int brightness = 128;
  int num_leds = 50;
  while (true) {
    for(int i = 0; i < num_leds; i++) {
      leds[i] = CHSV(hue++, 255, brightness);
      FastLED.show();
      fadeToBlackBy(leds, num_leds, 50);
      delay(50);
    }
    for(int i = num_leds - 1; i >= 0; i--) {
      leds[i] = CHSV(hue++, 255, brightness);
      FastLED.show();
      fadeToBlackBy(leds, num_leds, 50);
      delay(50);
    }
  }
}