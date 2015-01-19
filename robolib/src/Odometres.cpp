
#include "PinChangeInt.h"

#define ODO_ENCL 1
#define ODO_PINL 8
#define ODO_ENCR 0
// ODO_PINR est 3

volatile long ODO_cpt[2] = {0L,0L};

void ODO_fcptL() {
  ++ODO_cpt[ODO_ENCL];
}
 
void ODO_fcptR() {
  ++ODO_cpt[ODO_ENCR];
}

void ODO_init() {
  attachInterrupt(ODO_ENCR,ODO_fcptR,CHANGE);
  //attachInterrupt(ODO_ENCL,ODO_fcptL,CHANGE);  
  PCattachInterrupt(ODO_PINL,ODO_fcptL,CHANGE);
}

long ODO_getL() {
  return ODO_cpt[ODO_ENCL];
}

long ODO_getR() {
  return ODO_cpt[ODO_ENCR];
}

void ODO_resetL(long c = 0L) {
  ODO_cpt[ODO_ENCL] = c;
}

void ODO_resetR(long c = 0L) {
  ODO_cpt[ODO_ENCR] = c;
}
