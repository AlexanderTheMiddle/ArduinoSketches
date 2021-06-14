void setup() {
  pinMode(12, OUTPUT);

}
double t = 0;
void loop() {
  digitalWrite(12, HIGH);
  delay(4*sin(radians(t)));
  digitalWrite(12, LOW);
  delay(4*sin(radians(t)));
  t = int(t+0.01)%360;
}
