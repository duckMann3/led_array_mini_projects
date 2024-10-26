#include<Arduino.h>
#include<FastLED.h>

#define LED_PIN         13
#define MIC_PIN         35
#define NUM_LEDS        64
#define BRIGHTNESS      128
#define MATRIX_WIDTH    8
#define MATRIX_HEIGHT   8
#define LED_TYPE        WS2812B
#define COLOR_ORDER     GRB

CRGB leds[NUM_LEDS];

int getLEDIndex(int x, int y);
void flashRow(int row);
int smoothMicValue();

void setup()
{
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
    FastLED.setBrightness(BRIGHTNESS);
    FastLED.clear();
    pinMode(MIC_PIN, INPUT);
}

void loop()
{
    int micValue = smoothMicValue();
    int row = map(micValue, 0, 1023, 0, MATRIX_HEIGHT - 1);
    flashRow(row);
}

int getLEDIndex(int x, int y)
{
    if(y % 2 == 0)
    {
        return y * MATRIX_WIDTH + x;
    }

    else
    {
        return y * MATRIX_WIDTH + (MATRIX_WIDTH - 1 - x);
    }
}

void flashRow(int row)
{
    FastLED.clear();
    for(int x = 0; x < MATRIX_WIDTH; x++)
    {
        int index = getLEDIndex(x, row);     
        leds[index] = CRGB::Green;
    }
    FastLED.show();
    delay(100);
}

int smoothMicValue()
{
  int total = 0;
  for(int i = 0; i < 10; i++)
  {
    total += analogRead(MIC_PIN);
    delay(10);
  }
  return total / 10;
}

