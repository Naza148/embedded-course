#include <Arduino.h>
#include "driver/adc.h"

#define BTN_PIN 13
#define LED_PIN 4
#define SENSOR_PIN 5

#define TURN_ON_THRESHOLD 0.3
#define TURN_OFF_THRESHOLD 1.8

int mode = 0;  // 0 - auto; 1 - on; 2 - off
int lastBtnState = HIGH;
int ledValue = LOW;

void ledOn();
void ledOff();

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  pinMode(BTN_PIN, INPUT_PULLUP);

  analogReadResolution(12);
  analogSetPinAttenuation(SENSOR_PIN, ADC_11db);
}

void loop() {
  bool currentBtnState = digitalRead(BTN_PIN);

  if (currentBtnState == LOW && lastBtnState == HIGH) {
    mode++;

    if (mode > 2) {
      mode = 0;
    }

    Serial.printf("Button mode: %d\n", mode);
  }

  lastBtnState = currentBtnState;

  int sendorRaw = analogRead(SENSOR_PIN);
  float volt = sendorRaw * 3.3 / 4096.0;

  //Serial.printf("Sensor raw: %d, volt: %.3f\n", sendorRaw, volt);

  switch (mode) {
    case 0:
      if (volt < TURN_ON_THRESHOLD) {
        ledOn();
      } else if (volt > TURN_OFF_THRESHOLD) {
        ledOff();
      }
      break;

    case 1:
      ledOn();
      break;

    case 2:
      ledOff();
      break;
  }

  delay(20);
}

void ledOn() {
  if (ledValue != HIGH) {
    digitalWrite(LED_PIN, HIGH);
    ledValue = HIGH;
  }
}

void ledOff() {
  if (ledValue != LOW) {
    digitalWrite(LED_PIN, LOW);
    ledValue = LOW;
  }
}