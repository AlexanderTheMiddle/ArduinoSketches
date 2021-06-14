void setup() {
  Serial.begin(9600);
  //pinMode(A1, INPUT_PULLUP);

}

void loop() {
  Serial.println(analogRead(A1));
  delay(5);

}
