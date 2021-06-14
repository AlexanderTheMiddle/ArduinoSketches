void setup() {
  Serial.begin(9600);
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
}

void loop() {
  digitalWrite(5, HIGH);
  digitalWrite(4, LOW);
  Serial.print("1");
  delay(2000);
  digitalWrite(4, HIGH);
  digitalWrite(5, LOW);
  Serial.print("0");
  delay(2000);
  
}
