#include <Servo.h>
Servo a;
#define i 3
void setup() {

  Serial.begin(9600);
  a.attach(i);

}

void loop() {
  a.write(map(analogRead(A0), 0, 1023, 0, 180));
  delay(10);
  Serial.println(map(analogRead(A0), 0, 1023, 0, 180));

}
