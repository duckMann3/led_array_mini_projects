#include<Arduino.h> 
#include <FastLED.h>

#define LED_PIN     13         // Pin where the data line is connected
#define NUM_LEDS    64        // Total number of LEDs in the 8x8 matrix
#define BRIGHTNESS  5       // Brightness of the LEDs (0-255)
#define MATRIX_WIDTH  8       // Matrix width
#define MATRIX_HEIGHT 8       // Matrix height
#define LED_TYPE    WS2812B   // LED type
#define COLOR_ORDER GRB       // Color order (can vary depending on the LED strip)


CRGB leds[NUM_LEDS];

void zigzag();
void center();
int getLEDIndex(int x, int y);


void setup() 
{
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();  // Start with all LEDs off
}

void loop() 
{
    // zigzag();    
    center();
}

void center()
{
    for(int i = 0; i < 64; i += 9)
    {
        leds[i] = CRGB::Red;
        FastLED.show();
        delay(50);
    }
    FastLED.clear();
    for(int i = 7; i <= 56; i += 7)
    {
        leds[i] = CRGB::Blue;
        FastLED.show();
        delay(50);
    }
}

void zigzag()
{
    // Light up LEDs from top to bottom
    fadeToBlackBy(leds, NUM_LEDS, 20);
    for (int y = 0; y < MATRIX_HEIGHT; y++) 
    {
        for (int x = 0; x < MATRIX_WIDTH; x++) 
        {
            int index = getLEDIndex(x, y);
            leds[index] = CRGB::Blue;   // Set the current LED to red
            FastLED.show();
            delay(50);                 // Adjust speed of lighting up
            //leds[index] = CRGB::Black; // Turn off the current LED after a short delay
        }
    }

    int gHue = 0;
    // Light up LEDs from bottom to top
    for (int y = MATRIX_HEIGHT - 1; y >= 0; y--) 
    {
        for (int x = 0; x < MATRIX_WIDTH; x++) 
        {
            int index = getLEDIndex(x, y);
            leds[index] = CHSV(gHue, 255, 192);  // Set the current LED to blue
            FastLED.show();
            delay(80);                 // Adjust speed of lighting up
            //leds[index] = CRGB::Black; // Turn off the current LED after a short delay
            gHue += 2;
        }
    }
}

// Function to calculate LED index based on row and column in a zigzag pattern
int getLEDIndex(int x, int y) 
{
  if (y % 2 == 0) 
  {
    // For even rows, go left to right
    return y * MATRIX_WIDTH + x;
  } 
  else 
  {
    // For odd rows, go right to left
    return y * MATRIX_WIDTH + (MATRIX_WIDTH - 1 - x);
  }
}