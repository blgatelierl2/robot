#ifndef ODOMETRES_H
#define ODOMETRES_H

void ODO_init();
long ODO_getL();
long ODO_getR();
void ODO_resetL(long c = 0L);
void ODO_resetR(long c = 0L);

#endif
