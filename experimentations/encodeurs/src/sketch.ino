
#include "PinChangeInt.h"

#define M1 4
#define E1 5
#define E2 6
#define M2 7

#define ENC1 0
#define ENC2 1

//volatile int enc[2] = {0,0};
volatile int e1 = 0;
volatile int e2 = 0;

#define EMIN 250

boolean alive = true;

int E;
int t = 0;

void setup() {
  Serial.begin(9600);
  Serial.println("Init");
  pinMode(M1,OUTPUT);
  digitalWrite(M1,LOW);
  pinMode(E1,OUTPUT);
  analogWrite(E1,0);
  pinMode(M2,OUTPUT);
  digitalWrite(M2,LOW);
  pinMode(E2,OUTPUT);
  analogWrite(E2,0);
  E = EMIN;
  t = 0;
  e1 = 0;
  e2 = 0;
  delay(2000);
  attachInterrupt(ENC1,enc1,CHANGE);
  PCattachInterrupt(8,enc2,CHANGE);
  Serial.println("Start");
  analogWrite(E1,EMIN);
  analogWrite(E2,EMIN);
}

void loop() {
  if (alive && t>10000) {
    alive = false;
    Serial.print(E);
    Serial.print(",");
    //Serial.print(enc[ENC1]);
    Serial.print((float)e1/20.);
    Serial.print(",");
    //Serial.println(enc[ENC2]);
    Serial.print((float)e2/20.);
    Serial.println("");
    /*noInterrupts();
    //enc[ENC1] = 0;
    //enc[ENC2] = 0;
    e1 = 0;
    e2 = 0;
    interrupts();*/
    //E += 10;
    //if (E>255) E = EMIN;
    t = 0;
    E = 0;
    analogWrite(E1,E);
    analogWrite(E2,E);    
    delay(2000);
    Serial.print(E);
    Serial.print(",");
    //Serial.print(enc[ENC1]);
    Serial.print((float)e1/20.);
    Serial.print(",");
    //Serial.println(enc[ENC2]);
    Serial.print((float)e2/20.);
    Serial.println("");
  }
  delay(100);
  t += 100;
}

void enc1() {
  //++enc[ENC1];
  e1 += 1;
}

void enc2() {
  //++enc[ENC2];
  e2 += 1;
}
