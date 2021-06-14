void setup() {
  Serial.begin(9600);
  pinMode(2, OUTPUT);
  digitalWrite(2, LOW);
}

void loop() {
  Serial.println("no tazing....");
  digitalWrite(2, LOW);
  delay(3000);
  Serial.println("TAZING");
  digitalWrite(2, HIGH);
  delay(1000);
}
