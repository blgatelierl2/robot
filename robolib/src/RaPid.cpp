
#include <Arduino.h>
#include "Moteurs.h"
#include "Odometres.h"

#define VPID_VMAX 220
#define VPID_P 0.28
#define VPID_I 0.2
#define VPID_D 0.08

#define VPID_DELTA 500
float VPID_dt = VPID_DELTA/1000.;

bool VPID_actif = false;
unsigned long VPID_Ot = 0L;
float VPID_vL = 0.;
float VPID_vR = 0.;
float VPID_vcL = 0.;
float VPID_vcR = 0.;
int VPID_sgnL = 1;
int VPID_sgnR = 1;
long VPID_OoL = 0L;
long VPID_OoR = 0L;
float VPID_IeL = 0;
float VPID_IeR = 0;
float VPID_OeL = 0.;
float VPID_OeR = 0.;
int VPID_motL = 0;
int VPID_motR = 0;

void VPID_reset() {
  VPID_dt = VPID_DELTA/1000.;
  VPID_actif = false;
  VPID_Ot = 0L;
  VPID_vL = 0.;
  VPID_vR = 0.;
  VPID_vcL = 0.;
  VPID_vcR = 0.;
  VPID_sgnL = 1;
  VPID_sgnR = 1;
  VPID_OoL = 0L;
  VPID_OoR = 0L;
  VPID_IeL = 0;
  VPID_IeR = 0;
  VPID_OeL = 0.;
  VPID_OeR = 0.;
  VPID_motL = 0;
  VPID_motR = 0;
}

void VPID_start(int vL, int vR) {
  //if (VPID_actif) VPID_stop();
  vL = constrain(vL,-VPID_VMAX,VPID_VMAX);
  vR = constrain(vR,-VPID_VMAX,VPID_VMAX);
  VPID_sgnL = (vL<0)?-1:1;
  VPID_sgnR = (vR<0)?-1:1;
  VPID_vcL = float(abs(vL));
  VPID_vcR = float(abs(vR));
  VPID_OoL = ODO_getL();
  VPID_OoR = ODO_getR();
  VPID_Ot = millis();
  VPID_actif = true;
}

void VPID_stop() {
  MOT_setMotors(0,0);
  VPID_reset();
}

void VPID_boucle() {
  if (!VPID_actif) return;
  unsigned long t = millis();
  if (t-VPID_Ot<VPID_DELTA) return;
  VPID_dt = float(t-VPID_Ot)/1000.;
  long oL = ODO_getL();
  long oR = ODO_getR();
  VPID_vL = float(oL-VPID_OoL)*6000./VPID_DELTA;
  VPID_vR = float(oR-VPID_OoR)*6000./VPID_DELTA;
  float eL = VPID_vcL-VPID_vL;
  float eR = VPID_vcR-VPID_vR;
  VPID_IeL += eL*VPID_dt;
  VPID_IeR += eR*VPID_dt;
  float pidL = VPID_P*eL + VPID_I*VPID_IeL + VPID_D*(eL-VPID_OeL)/VPID_dt;
  float pidR = VPID_P*eR + VPID_I*VPID_IeR + VPID_D*(eR-VPID_OeR)/VPID_dt;
  VPID_motL = constrain(VPID_motL+pidL,0,255);
  VPID_motR = constrain(VPID_motR+pidR,0,255);
  MOT_setMotors(VPID_sgnL*VPID_motL,VPID_sgnR*VPID_motR);
  VPID_Ot = t;
  VPID_OoL = oL;
  VPID_OoR = oR;
  VPID_OeL = eL;
  VPID_OeR = eR;
}
