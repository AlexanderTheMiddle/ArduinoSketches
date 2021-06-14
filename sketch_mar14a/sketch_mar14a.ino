#include <Servo.h>

Servo myServo;

void setup() {
  Serial.begin(9600);
  myServo.attach(8);

}

boolean state = false;

void loop() {
  float a = int(map(analogRead(A0), 0, 1023, 0, 180));
  Serial.println(a);
  myServo.write(a);
  //delay(2000);
  state = !state;

}
