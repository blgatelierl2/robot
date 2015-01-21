
float POS_x,POS_y;
long prevR,prevL;

void POS_maj() {
  long R = ODO_getR();
  int dR = (int)(R-prevR);
  prevR = R;
  long L = ODO_getL();
  int dL = (int)(L-prevL);
  prevL = L;
  POS_x = 
}

void POS_getX() {
  return POS_X;
}

void POS_getY() {
  return POS_y;
}
