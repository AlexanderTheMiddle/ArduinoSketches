void setup() {
  Serial.begin(9600);
  pinMode(10, INPUT_PULLUP);
}

void loop() {
  Serial.println(digitalRead(10));
  delay(10);
}
