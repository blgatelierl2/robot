
#include <Arduino.h>
#include "Odometres.h"

#define POS_TICK 2.08
// 1 tick en cm
#define POS_ENTRAXE 14.7
// entraxe en cm

float POS_x = 0.;
float POS_y = 0.;
float POS_a = 0.;
long POS_prevR = 0L;
long POS_prevL = 0L;

void POS_maj() {
  long R = ODO_getR();
  int dR = (int)(R-POS_prevR);
  POS_prevR = R;
  long L = ODO_getL();
  int dL = (int)(L-POS_prevL);
  POS_prevL = L;
  float dC = POS_TICK*(dR+dL)/2.;
  float dA = POS_TICK*(dR-dL)/POS_ENTRAXE;
  POS_a += dA;
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
