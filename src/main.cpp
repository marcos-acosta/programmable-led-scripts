#include <Arduino.h>
#include <FastLED.h>
#include <stdlib.h>

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

void bounce(int num_leds) {
  const int brightness = 128;
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

void snake() {
  const int brightness = 255;
  int position = rand() % TOTAL_NUM_LEDS;
  while (true) {
    int goal_position = rand() % TOTAL_NUM_LEDS;
    int distance_right = goal_position > position ? goal_position - position : TOTAL_NUM_LEDS - (goal_position - position);
    int direction = distance_right < TOTAL_NUM_LEDS / 2.0 ? 1 : -1;
    while (position != goal_position) {
      fadeToBlackBy(leds, TOTAL_NUM_LEDS, 50);
      leds[goal_position] = CRGB(255, 227, 69);
      leds[position] = CHSV(0, 0, brightness);
      FastLED.show();
      position = (position + direction) % TOTAL_NUM_LEDS;
    }
  }
}

void loop() {
  // int num_leds = 50;
  // bounce(num_leds);
  snake();
}