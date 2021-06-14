#include <String.h>

#define thisbyte 8
#define savebyte 9
#define showbytes 3


void setup() {
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  digitalWrite(9, 0);
  digitalWrite(8, 0);
  digitalWrite(7, 0);
  int ii[8] = { 0, 1, 7, 2, 3, 4, 5, 6};
  
  //int bytes[8] = { 0, 0, 0, 0, 0, 1, 0, 0};
  //all_off();
  
}
int periods[10000];
int t = 0;
int timerr = millis();
int q = 0;
int sum = 0;
void loop() {
  for(int tt = 0; tt < 50; tt++) {
    delay(1);
    while(digitalRead(A0)){}
    periods[tt] = millis() - timerr;
    timerr = millis();
    /*
    show_number(1);
    delay(2);
    show_number(0);
    */
  }
  q = 0;
  sum = 0;
  for(; periods[q] != 0; q++) {
    sum += periods[q];
  }
  if(sum/q < 256) ;//show_number(sum/q);
}
