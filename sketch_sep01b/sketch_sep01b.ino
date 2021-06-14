void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
}

void loop() {
  Serial.println(analogRead(10));
  delay(5);

}
