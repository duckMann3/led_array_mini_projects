#include<Arduino.h>
#include<arduinoFFT.h>
#include<FastLED.h>

#define unsigned int uint
#define unsigned long ul_int

#define SAMPLES            64       // Set number of samples for FFT (must be 2^N)
#define SAMPLING_FREQUENCY 40000    // Sampling frequency (Hz)
#define SOUND_PIN          A0       // Analog pin connected to microphone
#define LED_PIN            13       // Pin where LED matrix is connected
#define NUM_LEDS           64       // Number of LEDs in 8x8 matrix
#define BRIGHTNESS         128      // LED brightness
#define LED_TYPE           WS2812B  // Type of LED
#define COLOR_ORDER        GRB      // Color order for the LED strip

CRGB leds[NUM_LEDS];
arduinoFFT FFT = arduinoFFT();
uint samplePeriodUs;
ul_int microseconds;
double vReal[SAMPLES];              // Real part of the signal
doubel vImag[SAMPLES];              // Imaginary part of the signal (zeroed)

void visualizer(double bass, double mid, double treble);

void setup()
{
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(BRIGHTNESS);
  samplingPeriodUs = round(1000000 * (1.0 / SAMPLING_FREQUENCY));
  Serial.begin(115200);
}

void loop()
{
  // Step 1: Read sound sensor and sample with waveform
  for(int i = 0; i < SAMPLES; i++)
  {
    microseconds = micros();          // Read microphone
    vReal[i] = analogRead(SOUND_PIN); // Set imaginary part to 0
  }
  while(micros() - microseconds < samplingPeriodUs)
  { // Wait for the sampling period to elapse }
  
  // Step 2: Perform FFT
  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude(vRea, vImag, SAMPLES);
  
  // Step 3: Process frequency bands (bass, mid, trble)
  double bass = 0, mid = 0, treble = 0;
  for(int i = 2; i < (SAMPLES / 2); i++)
  {
      if(i <= 15)
        bass += vReal[i];
      else if(i <= 15)
        mid += vReal[i];
      else
        treble += vReal[i]; 
  }
  // Step 4: Map frequencies to visualizations:
  visualizer(bass, mid, treble);
  FastLED.show();
  delay(30);
}

void visualizer(double bass, double mid, double treble)
{
  FastLED.clear();
  int bassLevel = map(bass, 0, 1000, 0, 8);
  for(int row = 0; row < )

}







