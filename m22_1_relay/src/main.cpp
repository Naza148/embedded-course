#include <Arduino.h>

#define TRANSISTOR_PIN 4
#define RESULT_PIN 5

volatile unsigned long last_relay_changed_time = 0;
volatile bool relay_changed = false;

void transistor_update() {
  unsigned long current_time = millis();

  static unsigned long last_toogle = 0;
  static bool transistor_state = false;

  if (current_time - last_toogle >= 1000) {
    last_toogle = current_time;
    transistor_state = !transistor_state;

    digitalWrite(TRANSISTOR_PIN, transistor_state);

    Serial.printf("Transistor changed: %d\n", current_time);
  }
}

void relay_change() {
  relay_changed = true;
  last_relay_changed_time = millis();
}

void setup() {
  Serial.begin(115200);

  pinMode(TRANSISTOR_PIN, OUTPUT);
  pinMode(RESULT_PIN, INPUT_PULLUP);

  attachInterrupt(digitalPinToInterrupt(RESULT_PIN), relay_change, FALLING);
}

void loop() {
  unsigned long current_time = millis();

  transistor_update();

  if (relay_changed && current_time - last_relay_changed_time >= 20) {
    relay_changed = false;
    Serial.printf("Relay changed: %d\n", last_relay_changed_time);
  }
}