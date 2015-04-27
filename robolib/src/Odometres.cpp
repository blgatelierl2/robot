
#include "PinChangeInt.h"

#define ODO_ENCL 0
// ODO_PINL est 3
#define ODO_PINR 8
#define ODO_ENCR 1

volatile long ODO_cpt[2] = {0L,0L};

void ODO_fcptL() {
  ++ODO_cpt[ODO_ENCL];
}
 
void ODO_fcptR() {
  ++ODO_cpt[ODO_ENCR];
}

void ODO_init() {
  attachInterrupt(ODO_ENCL,ODO_fcptL,CHANGE);
  //attachInterrupt(ODO_ENCR,ODO_fcptR,CHANGE);  
  PCattachInterrupt(ODO_PINR,ODO_fcptR,CHANGE);
}

long ODO_getL() {
  return ODO_cpt[ODO_ENCL];
}

long ODO_getR() {
  return ODO_cpt[ODO_ENCR];
}

void ODO_setL(long c) {
  ODO_cpt[ODO_ENCL] = c;
}

void ODO_setR(long c) {
  ODO_cpt[ODO_ENCR] = c;
}

void ODO_reset() {
  ODO_setR(0L);
  ODO_setL(0L);
}
