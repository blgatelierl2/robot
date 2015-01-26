
#define ULT_PWM 3
// PWM Output 0－50000US，Every 50US represent 1cm
#define ULT_TRIG 5
// PWM trigger pin
 
unsigned int Distance=0;
uint8_t EnPwmCmd[4] = {0x44,0x02,0xbb,0x01};    // distance measure command
 
void setup(){                                 // Serial initialization
  Serial.begin(9600);                         // Sets the baud rate to 9600
  PWM_Mode_Setup();
}
 
void loop()
{
 PWM_Mode();
 delay(20);
}                      //PWM mode setup function
 
void PWM_Mode_Setup(){
  pinMode(URTRIG,OUTPUT);                     // A low pull on pin COMP/TRIG
  digitalWrite(URTRIG,HIGH);                  // Set to HIGH
  
  pinMode(URPWM, INPUT);                      // Sending Enable PWM mode command
  
  for(int i=0;i<4;i++){
      Serial.write(EnPwmCmd[i]);
   }
}
 
void PWM_Mode(){                              // a low pull on pin COMP/TRIG  triggering a sensor reading
    digitalWrite(URTRIG, LOW);
    digitalWrite(URTRIG, HIGH);               // reading Pin PWM will output pulses
     
    unsigned long DistanceMeasured=pulseIn(URPWM,LOW);
     
    if(DistanceMeasured>=50000){              // the reading is invalid.
      Serial.println("Invalid");   
    }
    else{
      Distance=DistanceMeasured/50;           // every 50us low level stands for 1cm
      Serial.print("Distance=");
      Serial.print(Distance);
      Serial.println("cm");
   }
}
