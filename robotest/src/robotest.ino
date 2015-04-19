
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

#include "Moteurs.h"
#include "Odometres.h"
//#include "Position.h"

void setup() {
  Serial1.begin(9600);
  MOT_init();
  ODO_init();
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
      if (p*d>=0) MOT_setMotors(pf,p);
      else MOT_setMotors(p,pf);
    }
    else if (c[0]=='S') {
      p = c[1];
      if (p<50) p = 0;
      if (0<=c[2] && c[2]<64) {
        pf = int(float(p)*(-1.+2.*float(c[2])/64.));
        MOT_setMotors(-p,-pf);
      }
      else if (64<=c[2] && c[2]<128) {
        pf = int(float(p)*(1.-2.*float(c[2]-64)/64.));
        MOT_setMotors(-pf,-p);
      }
      else if (128<=c[2] && c[2]<192) {
        pf = int(float(p)*(-1.+2.*float(c[2]-128)/64.));
        MOT_setMotors(p,pf);
      }
      else {
        pf = int(float(p)*(1.-2.*float(c[2]-192)/64.));
        MOT_setMotors(pf,p);
      }
    }
    /*else if (c[0]=='P') {
      int hx = int(10*POS_getX());
      int hy = int(10*POS_getY());
      int ha = int(180*POS_getA()/3.14);
      Serial1.write((uint8_t*)&hx,2);
      Serial1.write((uint8_t*)&hy,2);
      Serial1.write((uint8_t*)&ha,2);
      }*/
  }

  //POS_maj();
  
  delay(10);
}