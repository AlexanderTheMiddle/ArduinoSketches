#define LLpin 6

boolean LL_up = 1;
void setup() {
  attachInterrupt(1, LLf, RISING);
  pinMode(LLpin, OUTPUT);
}

int speedzero = 70;
int LLspeed = 255;
void loop() {
  if(LL_up) LLspeed = 255;
  else LLspeed = speedzero;
  analogWrite(LLpin, LLspeed);
  delay(1);
}
void LLf() {
  LL_up = !LL_up;
}
