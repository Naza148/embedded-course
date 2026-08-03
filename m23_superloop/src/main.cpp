#include <Arduino.h>

#define LED_COUNT 3

int led_pins[] = {2, 20, 21};
int leds_interval[] = {200, 500, 1000};

unsigned long leds_last_time[LED_COUNT] = {0};
uint8_t leds_state[LED_COUNT] = {LOW};

void setup() {
  for (int i = 0; i < LED_COUNT; i++) {
    pinMode(led_pins[i], OUTPUT);
  }
}

void loop() {
  unsigned long current_time = millis();

  for (int i = 0; i < LED_COUNT; i++) {
    if (current_time - leds_last_time[i] >= leds_interval[i]) {
      leds_last_time[i] = current_time;
      leds_state[i] = !leds_state[i];

      digitalWrite(led_pins[i], leds_state[i]);
    }
  }
}