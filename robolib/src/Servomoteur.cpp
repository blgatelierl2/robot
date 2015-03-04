
#include <Arduino.h>
#include <Servo.h>

/* On boards other than the Mega, use of the library disables
   analogWrite() (PWM) functionality on pins 9 and 10, whether
   or not there is a Servo on those pins.
*/

#define SRV_PIN 9

Servo SRV_servo;

void SRV_init() {
  SRV_servo.attach(SRV_PIN);
}

void SRV_setAngle(int a) {
  SRV_servo.write(constrain(a,0,180));
}
