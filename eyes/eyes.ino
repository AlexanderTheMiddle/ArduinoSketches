#include <Servo.h>
Servo a[8];
Servo b;
Servo mouth;
void setup() {
  Serial.begin(9600);
  a[5].attach(A3);
  mouth.attach(10);
  b.attach(11);
  pinMode(4, INPUT_PULLUP);

}
int mouth_target = 180, mouth_state = 180;
int ttt = 0;
void loop() {
  ttt = map(analogRead(A0), 0, 1024, 0, 180);
  a[5].write(ttt);
  ttt = map(analogRead(A1), 0, 1024, 0, 180);
  b.write(ttt);
  mouth.write(mouth_state);
  Serial.println(mouth_target);
  if(!digitalRead(4)) {
    delay(10);
    if(!digitalRead(4)) {
      mouth_target = 131;
    }
  }
  if(mouth_target > mouth_state) mouth_state++;
  if(mouth_target < mouth_state) mouth_state--;
  if(mouth_state == 131) mouth_target = 180;
  delay(1);

}
//180 - 131 - 180
