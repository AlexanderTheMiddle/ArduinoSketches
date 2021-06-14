#include <Servo.h>
Servo myservo;  // create servo object to control a servo

int treshhold = 2;
void setup() {
  Serial.begin(9600);
  myservo.attach(14);  // attaches the servo on pin 9 to the servo object
  for(int i = 2; i < 8; i++) {
    pinMode(i, INPUT_PULLUP);
  }
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  
}

int target = 90, state = 0, dstep = 1;
int difference = 0, lastDifference = 1000;
boolean invert = false;
int invertCounter = 0;
long lastInvert = 0;

void loop() {
  for(int i = 2; i < 8; i++) {
    if(!digitalRead(i)) {
      target = (i-2)*36;
    }
  }
  if(!invert) state = map(analogRead(A2), 0, 1023, 0, 180);
  else state = map(1023 - analogRead(A2), 0, 1023, 0, 180);
  
  difference = state - target;
  
  if(difference > treshhold) {
    digitalWrite(9, HIGH);
    digitalWrite(10, LOW);
  }
  else if(difference < -treshhold) {
    digitalWrite(9, LOW);
    digitalWrite(10, HIGH);
  }
  else {
    digitalWrite(9, LOW);
    digitalWrite(10, LOW);
  }

  Serial.println(invertCounter);
  if(abs(lastDifference) < abs(difference)) {
    lastInvert = millis();
    invertCounter++;
    if(invertCounter > 18) {
      invert = !invert;
      
      invertCounter = 0;
    }
  }
  if(millis() - lastInvert > 20) invertCounter = 0;
  lastDifference = difference;
  delay(1);                           // waits for the servo to get there
}
