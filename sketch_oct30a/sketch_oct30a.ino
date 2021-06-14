#include <Servo.h>

Servo servos[12];
int pins[12] = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, A0};

void setup() {
  Serial.begin(9600);

  for(int i = 0; i < 12; i++) {
    servos[i].attach(pins[i]);
  }

}

void loop() {
  for(int j = 0; j < 180; j++) {
    for(int i = 0; i < 12; i++) {
      servos[i].write(j);
    }
    delay(20);
  }
  delay(500);
  for(int j = 180; j > 0; j--) {
    for(int i = 0; i < 12; i++) {
      servos[i].write(j);
    }
    delay(20);
  }
  delay(500);
}
