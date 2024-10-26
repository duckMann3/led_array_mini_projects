#include<Arduino.h>
#include<FastLED.h>

#define NUM_LEDS 64
#define BRIGHTNESS 5
#define LED_PIN 13
#define LED_TYPE WS2812B
#define COLOR_ORDER GRB

#define SNAKE_LENGTH 16          // Length of the snake (can adjust as needed)

CRGB leds[NUM_LEDS];

int spiralOrder[64] = {
    0,1,2,3,4,5,6,7,
    15,23,31,39,47,55,63,
    62,61,60,59,58,57,56,
    48,40,32,24,16,8,
    9,10,11,12,13,14,
    22,30,38,46,54,
    53,52,51,50,49,
    41,33,25,17,
    18,19,20,21,
    29,37,45,
    44,43,42,
    34,26,28,
    36,35,27
};

void setup()
{
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);
    FastLED.clear();
}
int snakeHeadIndex = 0;

void loop()
{
  // Create the snake effect by shifting colors along the spiral order
  for (int i = 0; i < SNAKE_LENGTH; i++) {
    // Calculate the position of each part of the snake
    int snakePartIndex = (snakeHeadIndex - i + NUM_LEDS) % NUM_LEDS;
    
    // Assign a color to each part of the snake, using HSV for rainbow effect
    leds[spiralOrder[snakePartIndex]] = CHSV((i * 16) % 255, 255, 255);
  }

  // Update the LEDs
  FastLED.show();

  // Move the snake forward by shifting the head index
  snakeHeadIndex = (snakeHeadIndex + 1) % NUM_LEDS;

  // Clear the tail of the snake
  leds[spiralOrder[(snakeHeadIndex - SNAKE_LENGTH + NUM_LEDS) % NUM_LEDS]] = CRGB::Black;

  delay(100);  // Adjust delay to change the snake's speed
}
