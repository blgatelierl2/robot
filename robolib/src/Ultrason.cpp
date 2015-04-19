
#include <Arduino.h>

/*
  Code MINIMAL pour le mode Serial

  Connexions (pins) :
  Ultrason      Romeo
  1 Vcc         +5V
  2 Gnd         Gnd
  8 RX          1 TX (Serial1)
  9 TX          0 RX (Serial1)
*/

// Commande serial lecture distance
const uint8_t ULT_DistReadCmd[4] = {0x22,0x00,0x00,0x22};

void ULT_init(){
  Serial1.begin(9600);
}

unsigned int ULT_getDistance(){
  byte c[4];
  Serial1.write(ULT_DistReadCmd,4);
  while (Serial1.available()<4) delay(10);
  Serial1.readBytes((char*)c,4);
  return (c[1]<<8)|c[2];
}
