
#include <Arduino.h>
#include <Servo.h>

#define SRV_PIN 8

Servo SRV_servo;

void SRV_init() {
  SRV_servo.attach(SRV_PIN);
}

void SRV_setAngle(int a) {
  SRV_servo.write(constrain(a,0,180));
}
