#include<Arduino.h>
#include<FastLED.h>

#define LED_PIN       13
#define MIC_PIN       35
#define NUM_LEDS      64
#define BRIGHTNESS    128
#define LED_TYPE      WS2812B
#define COLOR_ORDER   GRB

CRGB leds[NUM_LEDS];
boolean val = 0;

void flash()
{
  FastLED.clear();
  leds[0] = CRGB::Red;
  FastLED.show();
  delay(100);
}

void setup()
{
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  FastLED.clear();

  pinMode(MIC_PIN, INPUT);
  Serial.begin(9600);
}

void loop()
{
  val = digitalRead(MIC_PIN);
  Serial.println(val);

  if(val == 1)
  {
    flash();
  }
  else
  {
    FastLED.clear();
    leds[0] = CRGB::Blue;
    FastLED.show();
    delay(100);
  }
}
