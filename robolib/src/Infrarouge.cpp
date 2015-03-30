
#include <Arduino.h>

/*
  ATTENTION !  Le fil jaune du capteur (sortie) doit être branché sur 
  le port vert (pin) de la carte Romeo tandis que le fil vert du capteur (masse)
  doit être branché sur le port noir (masse) de la carte Romeo.
*/

#define IRD_PINL 10
#define IRD_PINC 11
#define IRD_PINR 12

void IRD_init() {
  pinMode(IRD_PINL, INPUT);
  pinMode(IRD_PINC, INPUT);
  pinMode(IRD_PINR, INPUT);
}

bool IRD_detectL() {
  return (digitalRead(IRD_PINL) == LOW);
}

bool IRD_detectC() {
  return (digitalRead(IRD_PINC) == LOW);
}

bool IRD_detectR() {
  return (digitalRead(IRD_PINR) == LOW);
}
