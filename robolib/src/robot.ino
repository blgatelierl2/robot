
#include "Moteurs.h"
#include "Odometres.h"

void setup() {
  Serial.begin(9600);
  MOT_init();
  ODO_init();
}

void loop() {
  Serial.println(ODO_getL());
  delay(20);
}
