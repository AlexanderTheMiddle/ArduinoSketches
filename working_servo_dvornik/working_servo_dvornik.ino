/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>
int serAngle = 90;
Servo myservo;  // create servo object to control a servo

int potpin = 0;  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin

void setup() {
  Serial.begin(9600);
  myservo.attach(14);  // attaches the servo on pin 9 to the servo object
  for(int i = 2; i < 8; i++) {
    pinMode(i, INPUT_PULLUP);
  }
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  
}

void loop() {
  for(int i = 2; i < 8; i++) {
    if(!digitalRead(i)) {
      serAngle = (i-2)*36;
    }
  }
  analogWrite(9, analogRead(A0)/4);
  analogWrite(10, analogRead(A1)/4);
  Serial.println(serAngle);
  myservo.write(serAngle);                  // sets the servo position according to the scaled value
  delay(15);                           // waits for the servo to get there
}
