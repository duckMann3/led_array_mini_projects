#include<Arduino.h>
#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 64

#define DATA_PIN 13

// Define the array of leds
CRGB leds[NUM_LEDS];

// Time scaling factors for each component
#define BRIGHTNESS      50
#define TIME_FACTOR_HUE 60
#define TIME_FACTOR_SAT 100
#define TIME_FACTOR_VAL 100

#define FRAMES_PER_SECOND 120
uint8_t gHue = 0;

void juggle();
void sinelon();

void setup() 
{
    Serial.begin(115200);
    FastLED.addLeds<WS2812, DATA_PIN, GRB>(leds, NUM_LEDS).setRgbw(RgbwDefault());
    FastLED.setBrightness(BRIGHTNESS);  // Set global brightness to 50%
    delay(2000);  // If something ever goes wrong this delay will allow upload.
}


void loop() 
{
    FastLED.delay(1000/FRAMES_PER_SECOND);
    sinelon();
    FastLED.show();
    EVERY_N_MILLISECONDS( 20 ) { gHue++; } // slowly cycle the "base color" through the rainbow
    // uint32_t ms = millis();
    
    // for(int i = 0; i < NUM_LEDS; i++) {
    //     // Use different noise functions for each LED and each color component
    //     uint8_t hue = inoise16(ms * TIME_FACTOR_HUE, i * 1000, 0) >> 8;
    //     uint8_t sat = inoise16(ms * TIME_FACTOR_SAT, i * 2000, 1000) >> 8;
    //     uint8_t val = inoise16(ms * TIME_FACTOR_VAL, i * 3000, 2000) >> 8;
        
    //     // Map the noise to full range for saturation and value
    //     sat = map(sat, 0, 255, 30, 255);
    //     val = map(val, 0, 255, 100, 255);
        
    //     leds[i] = CHSV(hue, sat, val);
    // }

    // Small delay to control the overall speed of the animation
    //FastLED.delay(1);
}

void juggle()
{
    fadeToBlackBy(leds, NUM_LEDS, 20);
    uint8_t dohue = 0;
    for(int i = 0; i < 8; i++)
    {
        leds[beatsin16(i+7, 0, NUM_LEDS-1)] |= CHSV(dohue, 200, 255);
        dohue += 32;
    }
}

void sinelon()
{
    fadeToBlackBy(leds, NUM_LEDS, 20);
    int pos = beatsin16(3, 0, NUM_LEDS-1);
    leds[pos] += CHSV(gHue, 255, 192);
}