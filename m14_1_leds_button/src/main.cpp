#include <Arduino.h>

#define LED1_PIN 4
#define LED2_PIN 5
#define MY_BTN_PIN 15
#define BOOT_BTN_PIN 0

bool fastMode = false;
int lastBlinkTime = 0;
bool ledTurnedOn = false;

void setup() {
  Serial.begin(115200);

  pinMode(LED1_PIN, OUTPUT);
  pinMode(LED2_PIN, OUTPUT);

  pinMode(MY_BTN_PIN, INPUT_PULLUP);
  pinMode(BOOT_BTN_PIN, INPUT_PULLUP);
}

void loop() {
  int myBtnState = digitalRead(MY_BTN_PIN);
  int bootBtnState = digitalRead(BOOT_BTN_PIN);

  if (myBtnState == LOW) {
    fastMode = true;
    Serial.println("Fast mode is turned ON");
  } else if (bootBtnState == LOW) {
    fastMode = false;
    Serial.println("Fast mode is turned OFF");
  }

  int blinkDelayTime = fastMode ? 200 : 1500;
  int time = millis();

  if (time > lastBlinkTime + blinkDelayTime) {
    if (ledTurnedOn) {
      digitalWrite(LED1_PIN, LOW);
      digitalWrite(LED2_PIN, LOW);

      ledTurnedOn = false;
    } else {
      digitalWrite(LED1_PIN, HIGH);
      digitalWrite(LED2_PIN, HIGH);

      ledTurnedOn = true;
    }

    lastBlinkTime = time;
  }

  delay(50);
}