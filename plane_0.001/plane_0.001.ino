
#include <Servo.h>

Servo motor;  // create servo object to control a servo

void setup() {
  motor.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
}

void loop() {
  for(int i = 800; i < 2301; i+=10) {
    motor.writeMicroseconds(i);
    delay(20);
  }
  delay(3000);
  motor.writeMicroseconds(800);    
  while(1){}// sets the servo position according to the scaled value
                          // waits for the servo to get there
}

//0 - 530
//800 - 2300
