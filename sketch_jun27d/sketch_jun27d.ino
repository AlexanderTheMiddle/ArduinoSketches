
#define motor 9
void setup() {
  pinMode(motor, OUTPUT);

}

void loop() {
  //oiuh
  analogWrite(motor, 0);
  delay(1000);
  for (int i = 0; i < 256; i++) {
    analogWrite(motor, i);
    delay(20);
  }
  delay(1000);
}
