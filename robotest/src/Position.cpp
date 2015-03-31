
#include <Arduino.h>
#include "Odometres.h"
#include "Moteurs.h"

#define POS_TICK 2.08
// 1 tick en cm
#define POS_ENTRAXE 14.7
// entraxe en cm

float POS_x = 0.;
float POS_y = 0.;
float POS_a = 0.;
long POS_prevR = 0L;
long POS_prevL = 0L;
int POS_signeR = 1;
int POS_signeL = 1;

void POS_reset() {
  POS_x = 0.;
  POS_y = 0.;
  POS_a = 0.;
  POS_prevR = 0L;
  POS_prevL = 0L;
  POS_signeR = 1;
  POS_signeL = 1;
}

void POS_maj() {
  int p = MOT_getR();
  if (p>0) POS_signeR = 1;
  else if (p<0) POS_signeR = -1;
  // sinon (puissance moteur à 0), on garde l'ancien signe
  long R = ODO_getR();
  int dR = POS_signeR*(int)(R-POS_prevR);
  POS_prevR = R;
  p = MOT_getL();
  if (p>0) POS_signeL = 1;
  else if (p<0) POS_signeL = -1;
  long L = ODO_getL();
  int dL = POS_signeL*(int)(L-POS_prevL);
  POS_prevL = L;
  float dC = POS_TICK*(float)(dR+dL)/2.;
  //float dA = POS_TICK*(float)(dR-dL)/POS_ENTRAXE;
  //POS_a += dA;
  POS_a = POS_TICK*(float)(POS_prevR-POS_prevL)/POS_ENTRAXE;
  POS_x += cos(POS_a)*dC;
  POS_y += sin(POS_a)*dC;
}

float POS_getX() {
  return POS_x;
}

float POS_getY() {
  return POS_y;
}

float POS_getA() {
  return POS_a;
}
