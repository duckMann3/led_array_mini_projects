#include<Arduino.h>

#define LED_PIN 13
#define SENSOR_PIN 12
boolean val = 0;

void setup()
{
  pinMode(LED_PIN, OUTPUT);
  pinMode(sensorPin, INPUT);
  Serial.begin(9600);
}

void loop()
{
  val = digitalRead(SENSOR_PIN);
  Serial.println(val);
  if(val == HIGH)
      digitalWrite(LED_PIN, HIGH);
  else
    digitalWrite(LED_PIN, LOW);
}
