#define motor 5

void setup() {
  pinMode(motor, OUTPUT);

}

void loop() {
  analogWrite(motor, 20);
  delay(1000);
  for (int i = 20; i < 154; i++) {
    analogWrite(motor, i);
    delay(50);
  }
  delay(1000);

}
