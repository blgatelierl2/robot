/*
  Exemple d'utilisation du capteur infrarouge.
  Source : http://www.dfrobot.com/wiki/index.php?title=Adjustable_Infrared_Sensor_Switch_%28SKU:SEN0019%29
  Le capteur est ici branché sur la pin 4.

  *ATTENTION*  Le fil jaune du capteur (sortie) doit être branché sur 
  le port vert (pin) de la carte Romeo tandis que le fil vert du capteur (masse)
  doit être branché sur le port noir (masse) de la carte Romeo !
*/

const int InfraredSensorPin = 4;//Connect the signal pin to the digital pin 4
const int LedDisp = 13;
 
void setup() {
  Serial.begin(57600);
  Serial.println("Start!"); 
  pinMode(InfraredSensorPin,INPUT);
  pinMode(LedDisp,OUTPUT);
  digitalWrite(LedDisp,LOW);
}
 
void loop() {
  if(digitalRead(InfraredSensorPin) == LOW)  digitalWrite(LedDisp,HIGH);
  else  digitalWrite(LedDisp,LOW);
  Serial.print("Infrared Switch Status:");
  Serial.println(digitalRead(InfraredSensorPin),BIN);
  delay(50);
}
