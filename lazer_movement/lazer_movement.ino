#include <Servo.h>
Servo servox;

Servo servoy;
#define xcoo A1
#define ycoo A2

void setup() {
  Serial.begin(9600);
  servox.attach(11);
  servoy.attach(10);
  pinMode(6, OUTPUT);
  digitalWrite(6, HIGH);
}
float x = 90.0;
float y = 90.0;
void loop() {
  
  Serial.print("X: ");
  Serial.print(analogRead(xcoo));
  Serial.print(" Y: ");
  Serial.println(analogRead(ycoo));
  if (analogRead(xcoo) < 400) x+=0.5;
  if (analogRead(xcoo) > 650) x-=0.5;
  if (x >180) x = 180;
  if (x < 0) x = 0;
  if (analogRead(ycoo) < 400) y+=0.5;
  if (analogRead(ycoo) > 650) y-=0.5 ;
  if (y >180) y = 180;
  if (y < 0) y = 0;
  
  servox.write(x);
  servoy.write(y);
  //delay(1);
}
