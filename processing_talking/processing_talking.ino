int x;

void setup() {
  Serial.begin(38400);

}

void loop() {
  if(Serial.available() > 0) {
    x = Serial.read();
  }
  if(x == '0' || x == '1') Serial.println(int(x) + 1 - int('0'));

}
