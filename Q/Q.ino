void setup() {
  Serial.begin(9600);

  pinMode(8, OUTPUT);
  digitalWrite(8, 1);
}

void loop() {
Serial.println(analogRead(A1));
  if (analogRead(A1) < 50) {
    Serial.println("Согнул руку");
    digitalWrite(8, 0);
    delay(100);
    digitalWrite(8, 1);
    delay(1000);
  }
  delay(1);
  //z == 0;

}
