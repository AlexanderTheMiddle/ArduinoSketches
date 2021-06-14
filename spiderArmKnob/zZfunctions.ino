int sgn(int a) {
  if(a < 0) return -1;
  else if(a == 0) return 0;
  else return 1;
}

int productOnTarget() {
  int prod = 1;
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 3; j++) {
      prod*=onTarget[i][j];
    }
  }
  return prod;
}
