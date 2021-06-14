/*
 Controlling a servo position using a potentiometer (variable resistor)
 by Michal Rinott <http://people.interaction-ivrea.it/m.rinott>

 modified on 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Knob
*/

#include <Servo.h>

Servo myservo; 
Servo myservoq; // create servo object to control a servo


void setup() {
  pinMode(A0, INPUT_PULLUP);
  myservo.attach(5);
  myservoq.attach(6);// attaches the servo on pin 9 to the servo 
  myservo.write(0);  
  myservoq.write(0);
  delay(2000); 
}





void loop() {
  if(digitalRead(A0)) {
for(float i = 0.0; i < 181.0; i += 1.0) {
  myservo.write(i);  
  myservoq.write(int(i / 5.0 * 2.0));  
  delay(1);
  }
  delay(300);
  myservoq.write(180); 
  delay(700);
  for(int i = 180; i >= 0; i--) {
  myservo.write(i); 
  myservoq.write(i);   
  delay(1);

  }
  }


}
