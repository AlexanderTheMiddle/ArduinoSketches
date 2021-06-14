#include <GyverEncoder.h>

Encoder enc1(5, 6, 7), enc2(8, 9, 10);
void setup() {
  Serial.begin(9600);
  enc1.setType(TYPE2);
  enc2.setType(TYPE2);
  
}
float v1 = 0, v2 = 0, maxx = 18, stepp = 1;
boolean jump1 = false, jump2 = false;
void loop() {
  enc1.tick();
  enc2.tick();
  if(enc1.isTurn()) {
    if(enc1.isRight()) v1 = constrain(v1+stepp, 0, maxx);
    if(enc1.isLeft()) v1 = constrain(v1-stepp, 0, maxx);
  }
  if(enc2.isTurn()) {
    if(enc2.isRight()) v2 = constrain(v2+stepp, 0, maxx);
    if(enc2.isLeft()) v2 = constrain(v2-stepp, 0, maxx);
  }
  jump1 = !digitalRead(7);
  jump2 = !digitalRead(10);
  Serial.print(int(v1));
  Serial.print(",");
  Serial.print(jump1);
  Serial.print(",");
  Serial.print(int(v2));
  Serial.print(",");
  Serial.print(jump2);
  Serial.println(",");

  jump1 = false;
  jump2 = false;
}

//pot
/*
void setup() {
  Serial.begin(9600);
  
}
int val1, val2;
void loop() {
  val1 = constrain(map(analogRead(A0), 0, 1023, 0, 18), 0, 18);
  val2 = 18 - val1;
  Serial.println(String(val1) + "," + String(val2) + ",");

}

*/
