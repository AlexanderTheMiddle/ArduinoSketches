/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>

Servo bigser;  // create servo object to control a servo


int val;    // variable to read the value from the analog pin

void setup() {
  bigser.attach(7);  // attaches the servo on pin 9 to the servo object
}

void loop() {
bigser.write(95);
delay(100);
}
