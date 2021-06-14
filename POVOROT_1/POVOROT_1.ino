
#include <Servo.h>
#define pot 9
#define potmaxangle 270.0

Servo locot_servo;

void setup() {
  Serial.begin(9600);
  locot_servo.attach(11);
  
}
void loop() {
  
  int angle = constrain((analogRead(pot) - 210 )/ 8, 0, 180);
  
  if ( angle < 11) angle = 11;
  if ( angle > 69) angle = 69;
 locot_servo.write(angle);
 
 
 Serial.println(angle);
 delay(3);
  
  
}

// для сервы плеча
// )
 
