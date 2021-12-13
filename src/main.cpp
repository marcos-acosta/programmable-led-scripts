#include <Arduino.h>
#include <FastLED.h>
#include "player.hpp"
#include "physics_engine.hpp"

#define NUM_LEDS 300
#define LED_PORT 6

#define INPUT_PIN_1 2
#define INPUT_PIN_2 3
#define INPUT_PIN_3 4
#define INPUT_PIN_4 5

#define TOP_RIGHT_INDEX 76
#define RIGHT_TOP_INDEX 75

#define TOP_LEFT_INDEX 223
#define LEFT_TOP_INDEX 225
#define TOP_LENGTH (TOP_LEFT_INDEX - TOP_RIGHT_INDEX)

// defining led array
CRGBArray<NUM_LEDS> leds;

uint64_t current_millis;
void (*current_function)();

// function forward declarations
void clear_leds();
void riggs_plaza_message();
void yin_yang();
void snake();
void color_wave();
void meteor();
void twinkle();
void lightsaber_battle();
void polyrhythm();
void pleasant();
void snowflakes();

// helper functions
uint64_t get_elapsed_time(uint64_t curr_time) {
  return current_millis - curr_time;
}

void setup_pins() {
  pinMode(INPUT_PIN_1, INPUT_PULLUP);
  pinMode(INPUT_PIN_2, INPUT_PULLUP);
  pinMode(INPUT_PIN_3, INPUT_PULLUP);
  pinMode(INPUT_PIN_4, INPUT_PULLUP);
}

void dispatch_function() {
  static uint8_t last_func_code;
  static uint8_t func_code;

  uint8_t pin_1 = digitalRead(INPUT_PIN_4) << 3;
  uint8_t pin_2 = digitalRead(INPUT_PIN_3) << 2;
  uint8_t pin_3 = digitalRead(INPUT_PIN_2) << 1;
  uint8_t pin_4 = digitalRead(INPUT_PIN_1);

  func_code = 15 - (pin_1 | pin_2 | pin_3 | pin_4);

  if (last_func_code != func_code) {
    clear_leds();
    last_func_code = func_code;
  }

  switch(func_code) {
    case 0:
      current_function = &clear_leds;
      break;
    case 1:
      current_function = &riggs_plaza_message;
      break;
    case 2:
      current_function = &yin_yang;
      break;
    case 3:
      current_function = &snake;
      break;
    case 4:
      current_function = &meteor;
      break;
    case 5:
      current_function = &color_wave;
      break;
    case 6:
      current_function = &twinkle;
      break;
    case 7:
      current_function = &lightsaber_battle;
      break;
    case 8:
      current_function = &polyrhythm;
      break;
    case 9:
      current_function = &pleasant;
      break;
    case 10:
      current_function = &snowflakes;
      break;
    case 11:
      current_function = &clear_leds;
      break;
    case 12:
      current_function = &clear_leds;
      break;
    case 13:
      current_function = &clear_leds;
      break;
    case 14:
      current_function = &clear_leds;
      break;
    case 15:
      current_function = &clear_leds;
      break;
    default:
      break;
  }
}

// light show functions
void clear_leds() {
  for (size_t i = 0; i < NUM_LEDS; ++i)
    leds[i] = CHSV(0, 0, 0);
  
  FastLED.show();
}

void riggs_plaza_message() {
  static uint64_t prev_time;
  static const uint8_t DELAY = 50;

  static const uint8_t MESSAGE[] = {
    0b01100101, 0b01110110, 0b01100101, 0b01110010,
    0b01111001, 0b00100000, 0b01100100, 0b01100001,
    0b01111001, 0b00100000, 0b01101001, 0b01110011,
    0b00100000, 0b01100001, 0b00100000, 0b01110011,
    0b01110100, 0b01100101, 0b01110000, 0b00100000,
    0b01100011, 0b01101100, 0b01101111, 0b01110011,
    0b01100101, 0b01110010, 0b00100000, 0b01110100,
    0b01101111, 0b00100000, 0b01110100, 0b01101000,
    0b01100101, 0b00100000, 0b01110010, 0b01101001,
    0b01100111, 0b01100111, 0b01110011, 0b00100000,
    0b01110000, 0b01101100, 0b01100001, 0b01111010,
    0b01100001, 0b00100000, 0b01100111, 0b01110010,
    0b01100001, 0b01101110, 0b01100100, 0b00100000,
    0b01110010, 0b01100101, 0b01101111, 0b01110000,
    0b01100101, 0b01101110, 0b01101001, 0b01101110,
    0b01100111, 0b00000000, 0b00000000, 0b00000000
  };
  static size_t SIZE = 64 * 8;

  static uint8_t hue = 100;
  static uint8_t index, shift;
  static uint16_t counter;

  if (get_elapsed_time(prev_time) < DELAY)
    return;

  if (counter == 0)
    hue += 10;

  index = counter / 8;
  shift = 7 - counter % 8;

  // bubble up colors
  for (int j = min(SIZE, NUM_LEDS) - 1; j > 0; --j)
    leds[j] = leds[j - 1];

  leds[0] = CHSV(hue, 255, 255 * ((MESSAGE[index] >> (shift + 1)) % 2));
  
  (++counter) %= SIZE;
  
  FastLED.show();
  prev_time = millis();
}

void color_wave() {
  static uint8_t hue;
  static uint64_t prev_time;
  static const uint8_t DEFAULT_DELAY = 200;

  if (get_elapsed_time(prev_time) < DEFAULT_DELAY)
    return;

  for (uint16_t i = 0; i < NUM_LEDS; i++) {
    leds[i] = CHSV(hue,255,127);
  }
  hue++;

  prev_time = current_millis;
  FastLED.show();
}

void yin_yang() {
  static uint8_t hue_1 = 0b00000100;
  static uint8_t hue_2 = 0b10011001;

  static uint64_t prev_time;
  static const uint8_t DELAY = 23;
  static uint16_t index;

  static const uint8_t FADE = 30;
  static const size_t TAIL_LEN = 30;
  static const uint8_t START_TAIL = (NUM_LEDS - 1) / 2;
  static const uint8_t END_TAIL = (NUM_LEDS - 1) / 2 + (TAIL_LEN / 2);

  if (get_elapsed_time(prev_time) < DELAY)
    return;

  leds.fadeToBlackBy(FADE);

  bool should_merge = START_TAIL <= index && index <= END_TAIL;
  static uint8_t midpoint = (max(hue_1, hue_2) - min(hue_1, hue_2)) / 2;  

  leds[index] = CHSV(!should_merge * hue_1 + should_merge * midpoint, 255, 255);
  leds[NUM_LEDS - index - 1] = CHSV(!should_merge * hue_2 + should_merge * midpoint, 255, 255);

  // variable bookkeeping
  (++index) %= NUM_LEDS;

  if (index == 0) {
    hue_1 -= 5;
    hue_2 += 10;

    // swap colors so we don't wrap around
    uint8_t temp = hue_1;
    hue_1 = hue_2;
    hue_2 = temp;
  }
  prev_time = millis();

  FastLED.show();
}

void snake() {
  static uint64_t prev_time;
  static const uint8_t DELAY = 23;
  
  static const int brightness = 255;
  static const CRGB GOAL_COLOR{255, 227, 69};
  static const CHSV SNAKE_COLOR{0, 0, brightness};
  
  static int position;
  static int goal_position;
  static int distance_right;
  static int direction;

  if (get_elapsed_time(prev_time) < DELAY)
    return;
  
  if (goal_position == position) {
    goal_position = rand() % NUM_LEDS;
    distance_right = goal_position > position ? goal_position - position : NUM_LEDS - (position - goal_position);
    direction = distance_right < NUM_LEDS / 2 ? 1 : -1;
  }

  fadeToBlackBy(leds, NUM_LEDS, 35);

  leds[goal_position] = GOAL_COLOR;
  leds[position] = SNAKE_COLOR;
  (position += direction) %= NUM_LEDS;
  if (position < 0)
    position += NUM_LEDS;
  
  prev_time = millis();
  FastLED.show();
}

void meteor() {
  static uint64_t prev_time;

  // constants
  static const uint8_t DEFAULT_DELAY = 1;
  static const uint16_t MIN_WAIT = 500;
  static const uint16_t MAX_WAIT = 20000;
  static const uint8_t FADE = 75;
  static const CHSV METEOR_COLOR{170, 8, 128};
  static const int8_t MOVE_AMOUNT_MAGNITUDE = 2;

  // state variables
  static uint16_t delay = DEFAULT_DELAY;
  static uint16_t index = TOP_RIGHT_INDEX;
  static uint16_t end_index = TOP_LEFT_INDEX;
  static int8_t move_amount = MOVE_AMOUNT_MAGNITUDE;

  if (get_elapsed_time(prev_time) < DEFAULT_DELAY)
    return;

  // checks to see if it is time for a new meteor and dims all lights
  if (get_elapsed_time(prev_time) < delay) {
    leds.fadeToBlackBy(50);
    FastLED.show();
    return;
  }

  // reset the meteor delay to default
  delay = DEFAULT_DELAY;
  
  leds.fadeToBlackBy(FADE);
  leds[index] = METEOR_COLOR;

  index += move_amount;
  
  // logic to determiine where the meteor starts from
  bool initialize_move = 
    (move_amount > 0 && index >= end_index) ||
    (move_amount < 0 && index <= end_index);

  if (initialize_move) {
    bool new_direction = rand() % 2;

    index = new_direction ? TOP_RIGHT_INDEX : TOP_LEFT_INDEX;
    end_index = new_direction ? TOP_LEFT_INDEX : TOP_RIGHT_INDEX;
    move_amount = MOVE_AMOUNT_MAGNITUDE * (new_direction ? 1 : -1);

    delay = MIN_WAIT + rand() % (MAX_WAIT - MIN_WAIT);
  }

  prev_time = current_millis;
  FastLED.show();
}

void twinkle() {
  static uint64_t prev_time;
  static const uint16_t DELAY = 50;
  static const uint8_t STAR_HUE = 170;
  static const uint8_t STAR_SATURATION = 8;
  static const uint8_t MAX_BRIGHTNESS = 64;
  static const uint8_t NEW_STAR_PROBABILITY = 9;
  static const uint8_t DESPAWN_PROBABILITY = 3;

  // Uses arbitrary brightness scale; max value must be odd
  static const uint8_t MAX_STAR_VAL = 41;
  static uint8_t stars[TOP_LENGTH] = {0};
  uint8_t new_index;

  if (get_elapsed_time(prev_time) < DELAY)
    return;

  if (rand() % 100 < NEW_STAR_PROBABILITY) {
    // A star is born
    // ensure that the new index does not coincide with a star that already exists
    do {
      new_index = rand() % TOP_LENGTH;
    } while (stars[new_index] > 0);
    
    stars[new_index] = 1;
  }

  // reset all values
  for (uint8_t i = 0; i < TOP_LENGTH; ++i) {
    if (stars[i] == MAX_STAR_VAL) {
      if (rand() % 100 < DESPAWN_PROBABILITY) {
        --stars[i];
      }
    }
    // Brightness increment / decrement is based on the parity of its star value
    else if (stars[i] > 0) {
      stars[i] += (stars[i] % 2 == 0) ? -2 : 2;
    }

    leds[TOP_RIGHT_INDEX + i] = CHSV(STAR_HUE, STAR_SATURATION, MAX_BRIGHTNESS * stars[i] / MAX_STAR_VAL);
  }

  prev_time = current_millis;
  FastLED.show();
}

void lightsaber_battle() {
  static uint64_t prev_time;
  static const uint16_t DELAY = 20;
  static const uint8_t FADE = 40;

  static Player p1{CRGB(128, 0, 0), 30, (uint16_t) ((rand() % TOP_LENGTH) + TOP_RIGHT_INDEX), 30, 1, TOP_RIGHT_INDEX, TOP_LEFT_INDEX, 70, 4};
  static Player p2{CRGB(0, 0, 128), 30, (TOP_LEFT_INDEX + TOP_RIGHT_INDEX) / 2, 30, 1, TOP_RIGHT_INDEX, TOP_LEFT_INDEX, 70, 4};
  static PhysicsEngine engine{leds, p1, p2, TOP_RIGHT_INDEX, TOP_LEFT_INDEX};

  if (get_elapsed_time(prev_time) < DELAY)
    return;

  leds.fadeToBlackBy(FADE);
  ++engine;

  prev_time = current_millis;
  FastLED.show();
}

void polyrhythm() {
  static uint64_t prev_time;
  static const uint16_t DELAY = 20;
  static const uint8_t FADE = 40;

  static Player p1{CRGB(128, 0, 0), 10, 0, 40, 0, 0, TOP_RIGHT_INDEX - 2, 40, 0};
  static Player p2{CRGB(0, 0, 128), 10, TOP_LEFT_INDEX, -30, 0, TOP_LEFT_INDEX + 2, NUM_LEDS - 1, 30, 0};

  if (get_elapsed_time(prev_time) < DELAY)
    return;

  leds.fadeToBlackBy(FADE);
  ++p1; ++p2;

  leds[p1.getPos()] += p1.getColor();
  leds[NUM_LEDS - (p2.getPos() - p2.getMinPos()) - 1] += p2.getColor();

  prev_time = current_millis;
  FastLED.show();
}

void pleasant() {
  static uint64_t prev_time;
  static const uint16_t DELAY = 200;

  if (get_elapsed_time(prev_time) < DELAY)
    return;

  for (uint16_t i = 0; i < NUM_LEDS; ++i) {
    leds[i] = CHSV(41, 255, 128);
  }

  prev_time = current_millis;
  FastLED.show();
}

void snowflakes() {
  static uint64_t prev_time;
  static const uint16_t DELAY = 200;
  static const uint8_t hue = 128;
  static const uint8_t PROB_GENERATE = 60;

  if (get_elapsed_time(prev_time) < DELAY)
    return;

  bool generate_left = (rand() % 100) < PROB_GENERATE;
  uint8_t value_left = (rand() % 17) * 9 * generate_left;

  bool generate_right = (rand() % 100) < PROB_GENERATE;
  uint8_t value_right = (rand() % 17) * 9 * generate_right;

  // snowflakes descend
  for (uint8_t i = 0; i < RIGHT_TOP_INDEX; ++i) {
    leds[i] = leds[i + 1];
    leds[NUM_LEDS - i - 1] = leds[NUM_LEDS - i - 2];
  }

  // generate new snowflake if necessary
  leds[RIGHT_TOP_INDEX] = CHSV(hue, 160, value_right);
  leds[LEFT_TOP_INDEX] = CHSV(hue, 160, value_left);

  prev_time = current_millis;
  FastLED.show();
}

void setup() {
  // instantiating array
  setup_pins();
  FastLED.addLeds<NEOPIXEL,LED_PORT>(leds, NUM_LEDS);
  Serial.begin(9600);

  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  current_millis = millis();
  dispatch_function();

  current_function();
}
