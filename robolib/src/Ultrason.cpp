
#include <Arduino.h>

#define ULT_PWM 11
// PWM Output 0－50000US，Every 50US represent 1cm
// Pin 4 du module
#define ULT_TRIG 12
// PWM trigger pin
// Pin 6 du module

/* Mode PWM
const uint8_t EnPwmCmd[4] = {0x44,0x02,0xbb,0x01};
*/

// Commande serial lecture distance
const uint8_t DistReadCmd[4] = {0x22,0x00,0x00,0x22};

void ULT_init(){
  Serial1.begin(9600);
  /* Mode PWM 
     pinMode(ULT_TRIG, OUTPUT); // A low pull on pin COMP/TRIG
     digitalWrite(ULT_TRIG, HIGH);
     pinMode(ULT_PWM, INPUT); // Sending Enable PWM mode command
     for(int i=0; i<4; ++i) Serial1.write(EnPwmCmd[i]);
  */
}

int ULT_getDistance(){
  char c[4];
  for(int i=0; i<4; ++i) Serial1.write(DistReadCmd[i]);
  while (Serial1.available()<4) delay(10);
  Serial1.readBytes(c,4);
  return int(c[1])*256+int(c[2]);
}

void ULT_setAngle(int a) {
  a = constrain(a,0,180)/4;
  char c[4];
  Serial1.write(0x22);
  Serial1.write(char(a));
  Serial1.write(0x00);
  Serial1.write((0x22+char(a))&0xff);
  while (Serial1.available()<4) delay(10);
  Serial1.readBytes(c,4);
}

/* Mode PWM
int ULT_getDistance(){
  // a low pull on pin COMP/TRIG  triggering a sensor reading
  digitalWrite(ULT_TRIG, LOW);
  digitalWrite(ULT_TRIG, HIGH); // reading Pin PWM will output pulses
  unsigned long d = pulseIn(ULT_PWM, LOW);
  return ((d>=50000)?-1:int(d/50));
  }*/
