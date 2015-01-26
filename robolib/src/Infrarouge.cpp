
#include <Arduino.h>

#define LED_PINR 9
#define LED_PING 10
#define LED_PINB 11

void LED_setColor(int r, int g, int b) {
  analogWrite(LED_PINR, r);
  analogWrite(LED_PING, g);
  analogWrite(LED_PINB, b);
}

void LED_init() {
  pinMode(LED_PINR, OUTPUT);
  pinMode(LED_PING, OUTPUT);
  pinMode(LED_PINB, OUTPUT);
  LED_setColor(0,0,0);
}
