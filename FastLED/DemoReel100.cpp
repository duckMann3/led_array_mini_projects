#include<Arduino.h>
#include<FastLED.h>

FASTLED_USING_NAMESPACE

#define DATA_PIN 	3
#define CLK_PIN 	4
#define LED_TYPE 	WS2811
#define COLOR_ORDER	GRB
#define NUM_LEDS	64
CRGB leds[NUM_LEDS];

#define BRIGHTNESS	   80
#define FRAMES_PER_SECOND  120

void rainbow(); 
void rainbow_with_glitter(); 
void confetti(); 
void sinelon(); 
void juggle(); 
void bpm(); 
void nextPattern(); 
