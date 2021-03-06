
#include <Servo.h>

Servo motor;  // create servo object to control a servo

int potpin = A0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin

void setup() {
  motor.attach(9);  // attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
}

void loop() {
  Serial.println(analogRead(A0));
  val = analogRead(potpin);            // reads the value of the potentiometer (value between 0 and 1023)
  val = map(val, 0, 1023, 800, 2300);     // scale it to use it with the servo (value between 0 and 180)
  motor.writeMicroseconds(val);                  // sets the servo position according to the scaled value
  //delay(15);                           // waits for the servo to get there
}

//0 - 530
