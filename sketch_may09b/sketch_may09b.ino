void setup() {
  Serial.begin(9600);

}

double a = -60;
void loop() {
  Serial.println(abs(a));
delay(10);
}
