#include <Arduino.h>

#define BUTTON_PIN 15

int16_t click_counter = 0;
bool buttonState = false;

void IRAM_ATTR click_reaction() {
  buttonState = true;
}

void setup() {
  Serial.begin(115200);

  pinMode(BUTTON_PIN, INPUT);
  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), click_reaction, FALLING);
}

void loop() {
  if (buttonState) {
    buttonState = false;
    click_counter++;

    Serial.println("\n Button Pressed! Count: " + String(click_counter));

    delay(10);
  }
}