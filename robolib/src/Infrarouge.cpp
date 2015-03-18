
#include <Arduino.h>

#define IRD_PINL 10
#define IRD_PINC 11
#define IRD_PINR 12

void IRD_init() {
  pinMode(IRD_PINL, INPUT);
  pinMode(IRD_PINC, INPUT);
  pinMode(IRD_PINR, INPUT);
}

boolean IRD_detectL() {
  return (digitalRead(IRD_PINL) == LOW);
}

boolean IRD_detectC() {
  return (digitalRead(IRD_PINC) == LOW);
}

boolean IRD_detectR() {
  return (digitalRead(IRD_PINR) == LOW);
}
