#include <Servo.h>

Servo myServo;

int servoPin = 5;
int servoGroundPin = 4;


void setup () {
  Serial.begin (9600);

  myServo.attach(servoPin);
  
  pinMode(servoGroundPin, OUTPUT);
  digitalWrite(servoGroundPin, HIGH);
 
}

void loop () { 
  myServo.write(0);
  delay(1000);
  myServo.write(180);
  delay(1000);
}
