#include <Servo.h>

Servo arm;

void setup() {
  Serial.begin(9600);
  arm.attach(6);
}

void loop() {
  arm.write(0);
  Serial.println(0);
  int timer = millis();
  while(millis() - timer < 4000);
  
  arm.write(180);
  Serial.println(180);
  timer = millis();
  while(millis() - timer < 4000);

}
