#include<Arduino.h>
#include<FastLED.h>

#define LED_PIN         13          // Pin where the data line is connected 
#define NUM_LEDS        64          // Total number of LEDS in the 8x8 matrix
#define BRIGHTNESS      128         // Brightness of the LEDs (0-255)
#define MATRIX_WIDTH    8           // Matrix width
#define  MATRIX_HEIGHT  8           // Matrix height
#define LED_TYPE        WS2812B     // LED type
#define COLOR_ORDER     GRB         // Color order (can vary depending on LED strip)

CRGB leds[NUM_LEDS];

int getLEDIndex();                  // Function to calc. LED index based on row & column in a zig-zag pattern
void setup()
{
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);
    FastLED.clear();                // Start with all LEDs off
}

void loop()
{
    // Light up LEDs from top to bottom:
    for(int y = 0; y < MATRIX_HEIGHT; y++)
    {
        for(int x = 0; x < MATRIX_WIDTH; x++)
        {
            int index = getLEDIndex(x, y);
            leds[index] = CRGB::Red;   // Set the current LED to red
            FastLED.show();
            delay(50);                 // Adjust speed of lighting up
            leds[index] = CRGB::Black; // Turn off the current LED after a short delay
        }
    }

    // Light up LEDs from botton to top
    for(int y = MATRIX_HEIGHT - 1; y >=0 ; y--)
    {
        for(int x = 0; x < MATRIX_WIDTH; x++)
        {
            int index = getLEDIndex(x, y);
            leds[index] = CRGB::Blue;  // Set the current LED to blue
            FastLED.show();
            delay(50);                 // Adjust the speed of lighting up
            leds[index] = CRGB::Black; // Turn off the current LED after a short delay
        }
    }

}

int getLEDIndex()
{
    // For even rows, go left to right
    if(y % 2 == 0)
    {
        return y * MATRIX_WIDTH + x;
    }
    // For odd rows,go righ to left 
    return y * MATRIX_WIDTH + (MATRIX_WIDTH - 1 - x);
}
