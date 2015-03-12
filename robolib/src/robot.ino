
#include "Led13.h"
#include "Moteurs.h"
#include "Odometres.h"
//#include "Servomoteur.h"
#include "Ultrason.h"
//#include "Position.h"
#include "Commande.h"

void setup() {
  Serial1.begin(9600);
  LED13_init();
  MOT_init();
  ODO_init();
  //SRV_init();
  ULT_init();
}

void loop() {
  CMD_recvOrdre();
}
