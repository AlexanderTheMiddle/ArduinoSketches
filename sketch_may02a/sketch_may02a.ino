#include <Servo.h>
Servo a;
void setup() {
  a.attach(10);
  Serial.begin(9600);

}
int value = 90;
void loop() {
  value = map(analogRead(A0), 0, 1023, 0, 180);
  a.write(value);
  Serial.println(value);
  delay(10);

}
