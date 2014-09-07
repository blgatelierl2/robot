const int ledR = 10;
const int ledG = 9;
const int ledB = 11;
int r = 255;
int g = 255;
int b = 255;

void setup() {
  pinMode(ledR, OUTPUT);
  pinMode(ledG, OUTPUT);
  pinMode(ledB, OUTPUT);
  analogWrite(ledR, r);
  analogWrite(ledG, g);
  analogWrite(ledB, b);
  randomSeed(analogRead(0));
}

void loop() {
  int nr, ng, nb;
  int steps = 50;
  nr = random(256);
  ng = random(256);
  nb = random(256);
  for (int i=0; i<steps; ++i) {
    analogWrite(ledR, r+(nr-r)*i/(steps-1));
    analogWrite(ledG, g+(ng-g)*i/(steps-1));
    analogWrite(ledB, b+(nb-b)*i/(steps-1));
    delay(50);
  }
  r = nr;
  g = ng;
  b = nb;
  delay(200);
}

