
#include <Arduino.h>
#include "Led13.h"
#include "Moteurs.h"
#include "Odometres.h"
#include "Servomoteur.h"
#include "Ultrason.h"
#include "Infrarouge.h"
#include "RaPid.h"

int CMD_fabInt(byte b0, byte b1) {
  return int(b0)|(int(b1)<<8);
}

void CMD_recvOrdre() {
  byte c[5];
  int p,pf,d;
  if (Serial.available()>=5) {
    Serial.readBytes((char*)c,5);
    if (c[0]=='m') {
      MOT_setMotors(CMD_fabInt(c[1],c[2]),CMD_fabInt(c[3],c[4]));
    }
    else if (c[0]=='l') {
      LED13_set(boolean(c[1]));
    }
    else if (c[0]=='o') {
      long V = ODO_getL();
      Serial.write((uint8_t*)&V,4);
      V = ODO_getR();
      Serial.write((uint8_t*)&V,4);
    }
    else if (c[0]=='s') {
      SRV_setAngle(int(c[1]));
    }
    else if (c[0]=='u') {
      int V = ULT_getDistance();
      Serial.write((uint8_t*)&V,2);
    }
    else if (c[0]=='i') {
      byte l = IRD_detectL()?1:0;
      byte c = IRD_detectC()?1:0;
      byte r = IRD_detectR()?1:0;
      Serial.write(l|(c<<1)|(r<<2));
    }
    else if (c[0]=='r') ODO_reset();
    else if (c[0]=='v') {
      int vL = CMD_fabInt(c[1],c[2]);
      int vR = CMD_fabInt(c[3],c[4]);
      if (vL==0 && vR==0) VPID_stop();
      else VPID_start(vL,vR);
    }
    else if (c[0]=='D') {
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
  }
  VPID_boucle();
}
