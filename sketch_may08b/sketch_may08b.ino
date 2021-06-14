#include <Servo.h>
Servo a[14];

void setup() {
  Serial.begin(9600);
  for(int i = 0; i < 14; i++) {
    a[i].attach(i);
    a[i].write(90);                                             <---- повернуть серву (работает)
  }
  for(int i = 0; i < 14; i++) {
    //a[i].write(90);                                             <---- повернуть серву (работает)
  }
  //a[1].write(60);                                                  <---- повернуть серву (не работает)
}

void loop() {
  delay(1000);
  
  //a[1].write(map(analogRead(A0), 0, 1023, 0, 180));                <---- повернуть серву (не работает)
  //a[1].write(60);                                                  <---- повернуть серву (не работает)
  
  delay(1000);
  Serial.println(map(analogRead(A0), 0, 1023, 0, 180));
  
   //a[1].write(160);                                                <---- повернуть серву (не работает)
 
}
