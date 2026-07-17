#include <Arduino.h>

#define LED_RED_PIN 4
#define LED_RED_CHANNEL 0

#define LED_BLUE_PIN 6
#define LED_BLUE_CHANNEL 1

#define LED_FREQ 2500
#define LED_RES 10
#define DUTY_MAX 1023
#define DUTY_DELTA 100

void turnOn(int ledChannel);
void turnOff(int ledChannel);

void setup() {
  ledcSetup(LED_RED_CHANNEL, LED_FREQ, LED_RES);
  ledcSetup(LED_BLUE_CHANNEL, LED_FREQ, LED_RES);

  ledcAttachPin(LED_RED_PIN, LED_RED_CHANNEL);
  ledcAttachPin(LED_BLUE_PIN, LED_BLUE_CHANNEL);
}

void loop() {
  turnOn(LED_RED_CHANNEL);
  delay(500);
  turnOff(LED_RED_CHANNEL);

  turnOn(LED_BLUE_CHANNEL);
  delay(500);
  turnOff(LED_BLUE_CHANNEL);
}

void turnOn(int ledChannel) {
  int duty = 0;

  for (; duty <= DUTY_MAX; duty += DUTY_DELTA) {
    ledcWrite(ledChannel, duty);
    delay(20);
  }

  if (duty != DUTY_MAX) {
    ledcWrite(ledChannel, DUTY_MAX);
  }
}

void turnOff(int ledChannel) {
  int duty = DUTY_MAX;

  for (; duty >= 0; duty -= DUTY_DELTA) {
    ledcWrite(ledChannel, duty);
    delay(20);
  }

  if (duty != 0) {
    ledcWrite(ledChannel, 0);
  }
}
