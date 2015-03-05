
#include <Arduino.h>

#define ULT_PWM 11
// PWM Output 0－50000US，Every 50US represent 1cm
// Pin 4 du module
#define ULT_TRIG 12
// PWM trigger pin
// Pin 6 du module

uint8_t EnPwmCmd[4] = {0x44,0x02,0xbb,0x01}; // distance measure command
 
void ULT_init(){
  Serial1.begin(9600); // Sets the baud rate to 9600
  pinMode(ULT_TRIG, OUTPUT); // A low pull on pin COMP/TRIG
  digitalWrite(ULT_TRIG, HIGH);
  pinMode(ULT_PWM, INPUT); // Sending Enable PWM mode command
  for(int i=0; i<4; ++i) Serial1.write(EnPwmCmd[i]);
}

int ULT_getDistance(){
  // a low pull on pin COMP/TRIG  triggering a sensor reading
  digitalWrite(ULT_TRIG, LOW);
  digitalWrite(ULT_TRIG, HIGH); // reading Pin PWM will output pulses
  unsigned long d = pulseIn(ULT_PWM, LOW);
  return ((d>=50000)?-1:int(d/50));
}
