
#include <Arduino.h>

#define LED13_PIN 13

void LED13_set(boolean on) {
  digitalWrite(LED13_PIN, on?HIGH:LOW);
}

void LED13_init() {
  pinMode(LED13_PIN, OUTPUT);
}
