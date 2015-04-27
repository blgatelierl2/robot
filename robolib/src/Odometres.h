#ifndef ODOMETRES_H
#define ODOMETRES_H

void ODO_init();
long ODO_getL();
long ODO_getR();
void ODO_setL(long c = 0L);
void ODO_setR(long c = 0L);
void ODO_reset();

#endif
