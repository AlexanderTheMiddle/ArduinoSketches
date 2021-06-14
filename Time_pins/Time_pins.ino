//int tp = 5;

int time_pins[5] = {10, 16, 9, 6, 5};

void setup() {
  for(int i = 0; i < 5; i++) {
    pinMode(time_pins[i], OUTPUT);
  }

}

void loop() {
  for(int i = 0; i < 5; i++) {
    digitalWrite(time_pins[i], HIGH);
  }
  delay(500);
  for(int i = 0; i < 5; i++) {
    for(int j = 254; j > -1; j--) {
      analogWrite(time_pins[i], j);
      delay(2);
    }
  }
  delay(200);


}
