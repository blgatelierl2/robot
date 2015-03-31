
#include <Arduino.h>

/*
  Code COMPLET pour le mode Serial

  Connexions (pins) :
  Ultrason      Romeo
  1 Vcc         +5V
  2 Gnd         Gnd
  5 MOTO        Controle de servomoteur eventuel
  8 RX          1 TX (Serial1)
  9 TX          0 RX (Serial1)
*/

#define ULT_DELAY 10

// Commande serial lecture distance
//const uint8_t DistReadCmd[4] = {0x22,0x00,0x00,0x22};
const uint8_t ULT_DistReadCmd = 0x22;
const uint8_t ULT_TempReadCmd = {0x11,0x00,0x00,0x11};

char ULT_a = 22;

void ULT_init(){
  Serial1.begin(9600);
}

int ULT_getDistance(){
  char c[4];
  Serial1.write(ULT_DistReadCmd);
  Serial1.write(ULT_a);
  Serial1.write(0x00);
  Serial1.write((ULT_DistReadCmd+ULT_a)&0xff);
  while (Serial1.available()<4) delay(ULT_DELAY);
  Serial1.readBytes(c,4);
  return (int(c[1])<<8)|int(c[2]);
}

// Regler l'angle de la commande servo
void ULT_setAngle(int a) {
  char c[4];
  ULT_a = char(constrain(a,0,180)/4);
  Serial1.write(ULT_DistReadCmd);
  Serial1.write(ULT_a);
  Serial1.write(0x00);
  Serial1.write((ULT_DistReadCmd+ULT_a)&0xff);
  while (Serial1.available()<4) delay(ULT_DELAY);
  Serial1.readBytes(c,4);
}

int ULT_getTemperature() {
  char c[4];
  Serial1.write(ULT_TempReadCmd,4);
  while (Serial1.available()<4) delay(ULT_DELAY);
  Serial1.readBytes(c,4);
  return ((int(c[1]) & 0x0f)<<8)+int(c[2]);
}
