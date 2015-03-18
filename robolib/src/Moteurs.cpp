
#include <Arduino.h>

#define MOT_DIR1 4
#define MOT_PWM1 5
#define MOT_PWM2 6
#define MOT_DIR2 7

int MOT_p1 = 0;
int MOT_p2 = 0;

void MOT_init() {
  pinMode(MOT_DIR1, OUTPUT);
  digitalWrite(MOT_DIR1, LOW);
  pinMode(MOT_PWM1, OUTPUT);
  analogWrite(MOT_PWM1, 0);
  pinMode(MOT_DIR2, OUTPUT);
  digitalWrite(MOT_DIR2, LOW);
  pinMode(MOT_PWM2, OUTPUT);
  analogWrite(MOT_PWM2, 0);
}

void MOT_setMot(int dir, int pwm, int p) {
  if (p>=0) digitalWrite(dir, LOW);
  else digitalWrite(dir, HIGH);
  analogWrite(pwm, abs(p));
}

void MOT_setL(int p) {
  p = constrain(p,0,255);
  MOT_p1 = p;
  MOT_setMot(MOT_DIR1,MOT_PWM1,p);
}

void MOT_setR(int p) {
  p = constrain(p,0,255);
  MOT_p2 = p;
  MOT_setMot(MOT_DIR2,MOT_PWM2,p);
}

int MOT_getL() {
  return MOT_p1;
}

int MOT_getR() {
  return MOT_p2;
}

void MOT_setMotors(int pL, int pR) {
  MOT_setL(pL);
  MOT_setR(pR);
}
