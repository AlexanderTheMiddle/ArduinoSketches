void physics() {
  g = map(analogRead(rotorPin), 0.0, 1023.0, -50.0, -300.0)/100.0;
  ax = 0.7*g;
  if(onTheGround && butReleased[0] && butReleased[2]) vx -= sgn(-vx)*ax;
  if(abs(vx) < 0.3) vx = 0;
  vy -= g;
  if(y + PLAYER_HEIGHT/2 + 2 >= floorHeight && vy > 0) {
    vy = 0;
    onTheGround = true;
  }
  x+=vx;
  y+=vy;
}

float sgn(float a) {
  if(a > 0) return 1;
  if(a < 0) return -1;
  else return 0;
}
