const int dirA = 7;
const int pwmA = 6;
const int dirB = 4;
const int pwmB = 5;
const int buzz = 8;
const int IRd = 9;
const int IRm = 10;
const int IRg = 11;

#include <SoftwareSerial.h>
SoftwareSerial mySerial(11, 12); // RX, TX

void setup(void) {
  mySerial.begin(9600);
  pinMode(dirA, OUTPUT);
  digitalWrite(dirA, LOW);
  pinMode(pwmA, OUTPUT);
  analogWrite(pwmA, 0);
  pinMode(dirB, OUTPUT);
  digitalWrite(dirB, LOW);
  pinMode(pwmB, OUTPUT);
  analogWrite(pwmB, 0);
}

void setMotor(int pwm, int dir, int p) {
  if (p>=0) digitalWrite(dir, LOW);
  else digitalWrite(dir, HIGH);
  analogWrite(pwm, abs(p));
}

void loop() {
  byte c[3];
  int p,d,pf;
  //while (Serial.available()>=4) Serial.read();
  if (mySerial.available()>=3) {
    mySerial.readBytes((char*)c,3);
    if (c[0]=='D') {
      p = 2*(c[1]-127);
      if (abs(p)<30) p = 0;
      d = 127-c[2];
      if (abs(d)<15) pf = p;
      else pf = int(float(p)*(1.-2.*float(abs(d))/127.));
      if (p*d>=0) {
        setMotor(pwmA, dirA, p);
        setMotor(pwmB, dirB, pf);
      }
      else {
        setMotor(pwmA, dirA, pf);
        setMotor(pwmB, dirB, p);
      }
    }
    else if (c[0]=='S') {
      p = c[1];
      if (p<50) p = 0;
      if (0<=c[2] && c[2]<64) {
        pf = int(float(p)*(-1.+2.*float(c[2])/64.));
        setMotor(pwmA, dirA, -pf);
        setMotor(pwmB, dirB, -p);
      }
      else if (64<=c[2] && c[2]<128) {
        pf = int(float(p)*(1.-2.*float(c[2]-64)/64.));
        setMotor(pwmA, dirA, -p);
        setMotor(pwmB, dirB, -pf);
      }
      else if (128<=c[2] && c[2]<192) {
        pf = int(float(p)*(-1.+2.*float(c[2]-128)/64.));
        setMotor(pwmA, dirA, pf);
        setMotor(pwmB, dirB, p);
      }
      else {
        pf = int(float(p)*(1.-2.*float(c[2]-192)/64.));
        setMotor(pwmA, dirA, p);
        setMotor(pwmB, dirB, pf);
      }
    }
  }
  delay(10);
}

