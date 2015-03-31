
#include <Arduino.h>

/*
  Code pour le mode PWM
 
  L'utilisation du mode PWM permet la lecture de la distance en largeur 
  d'impulsion sur la pin PWM du module. L'impulsion est envoyee a la
  demande suite a un passage a une tension LOW sur la pin Trig.
  
  Le mode serial est a privilegier.

  Connexions (pins) :
  Ultrason      Romeo
  1 Vcc         +5V
  2 Gnd         Gnd
  4 PWM         ULT_PWM (cf macro)
  6 Trig        ULT_TRIG (cf macro)
  8 RX          1 TX (Serial1)
  9 TX          0 RX (Serial1)
*/

#define ULT_PWM 11
// PWM Output 0－50000US，Every 50US represent 1cm
// Pin 4 du module
#define ULT_TRIG 12
// PWM trigger pin
// Pin 6 du module

const uint8_t EnPwmCmd[4] = {0x44,0x02,0xbb,0x01};

void ULT_init(){
  Serial1.begin(9600);
  pinMode(ULT_TRIG, OUTPUT); // A low pull on pin COMP/TRIG
  digitalWrite(ULT_TRIG, HIGH);
  pinMode(ULT_PWM, INPUT); // Sending Enable PWM mode command
  for(int i=0; i<4; ++i) Serial1.write(EnPwmCmd[i]);
}

int ULT_getDistance(){
  // a low pull on pin COMP/TRIG triggering a sensor reading
  digitalWrite(ULT_TRIG, LOW);
  digitalWrite(ULT_TRIG, HIGH); // reading Pin PWM will output pulses
  unsigned long d = pulseIn(ULT_PWM, LOW);
  return ((d>=50000)?-1:int(d/50));
}
