

int colour_pins[4] = {A0, A1, A2, A3};

void setup() {
  for(int i = 0; i < 4; i++) {
    pinMode(colour_pins[i], OUTPUT);
  }

}

void loop() {
  

  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 256; j++) {
      analogWrite(colour_pins[i], j);
      delay(2);
    }
    delay(300);
    for(int j = 254; j > -1; j--) {
      analogWrite(colour_pins[i], j);
      delay(2);
    }
    delay(300);
   
  }
  delay(500);
}
