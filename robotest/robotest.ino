/* 
  Du code pour piloter le robot par Bluetooth.
  Attention ! Contrairement a un Arduino, la carte Romeo V2
  a 2 interfaces materielles pour la communication serie :
  l'interface Serial (standard, qui est en particulier utilisee
  pour le transfert du programme) et l'interface Serial1
  a laquelle est connectee la socket Bluetooth de la carte.
  Le programme suivant utilise donc Serial1.

  A = M2 = Droite
  B = M1 = Gauche

*/

#define ENCG 0
#define ENCD 1

const int dirA = 7;
const int pwmA = 6;
const int dirB = 4;
const int pwmB = 5;
const int encA = ENGD+2;
const int encB = ENCG+2;
//const int buzz = 2;
//const int IRd = 8;
const int IRm = 9;
//const int IRg = 12;

int encompt[2] = {0,0};

/*#include "pitches.h"

void melodie() {
  int notes[] = {NOTE_E4,NOTE_DS4,NOTE_E4,NOTE_D4,NOTE_C4,NOTE_B4,NOTE_A3,NOTE_GS4,NOTE_A3};
  float durees[] = {0.5,0.5,3.,0.5,0.5,0.5,0.5,1.,4.};
  int tps = 300;
  int d;
  for (int i=0; i<9; ++i) {
    d = (int)(tps*durees[i]);
    tone(buzz,notes[i],d);
    delay(d);
  }
  noTone(buzz);
}*/

void setup(void) {
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(dirA, OUTPUT);
  digitalWrite(dirA, LOW);
  pinMode(pwmA, OUTPUT);
  analogWrite(pwmA, 0);
  pinMode(dirB, OUTPUT);
  digitalWrite(dirB, LOW);
  pinMode(pwmB, OUTPUT);
  analogWrite(pwmB, 0);
  pinMode(encA, INPUT);
  pinMode(encB, INPUT);
  /*pinMode(buzz, OUTPUT);
  melodie();*/
  //pinMode(IRd, INPUT);
  pinMode(IRm, INPUT);
  //pinMode(IRd, INPUT);
  
}

void setMotor(int pwm, int dir, int p) {
  //Serial.println(p);
  if (p>=0) digitalWrite(dir, LOW);
  else digitalWrite(dir, HIGH);
  analogWrite(pwm, abs(p));
}

int pA,pB;

void setMotors(int powA, int powB) {
  pA = powA;
  pB = powB;
  setMotor(pwmA, dirA, pA);
  setMotor(pwmB, dirB, pB);
}

void loop() {
  byte c[3];
  int p,pf,d;

  if (Serial1.available()>=3) {
    Serial1.readBytes((char*)c,3);
    if (c[0]=='D') {
      p = 2*(c[1]-127);
      if (abs(p)<30) p = 0;
      d = 127-c[2];
      if (abs(d)<15) pf = p;
      else pf = int(float(p)*(1.-2.*float(abs(d))/127.));
      if (p*d>=0) setMotors(p,pf);
      else setMotors(pf,p);
    }
    else if (c[0]=='S') {
      p = c[1];
      if (p<50) p = 0;
      if (0<=c[2] && c[2]<64) {
        pf = int(float(p)*(-1.+2.*float(c[2])/64.));
        setMotors(-pf,-p);
      }
      else if (64<=c[2] && c[2]<128) {
        pf = int(float(p)*(1.-2.*float(c[2]-64)/64.));
        setMotors(-p,-pf);
      }
      else if (128<=c[2] && c[2]<192) {
        pf = int(float(p)*(-1.+2.*float(c[2]-128)/64.));
        setMotors(pf,p);
      }
      else {
        pf = int(float(p)*(1.-2.*float(c[2]-192)/64.));
        setMotors(p,pf);
      }
    }
  }
  
  // Obstacle
  if (pA>0 && pB>0 && digitalRead(IRm)==LOW) setMotors(0,0);
  
  delay(100);
}

void codGz() {
  ++;
}
 
 
void RwheelSpeed() {
  coder[RIGHT] ++;
}
