#include <Servo.h>
Servo a;

void setup() {
  // put your setup code here, to run once:
  a.attach(5);
  
}

void loop() {
  a.write(90);
  // put your main code here, to run repeatedly:

}
