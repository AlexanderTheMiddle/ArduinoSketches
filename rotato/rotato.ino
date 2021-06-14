#include <math.h>
#include<TimerOne.h>

#define thisbyte 8
#define savebyte 9
#define showbytes 3

int ii[8] = { 0, 1, 7, 2, 3, 4, 5, 6};
int period;
long long timerr = millis();
boolean flag = 0;
double omega = 0.0, nowPosition = 0.0, nextPosition = 12.0;

void setup() {
  Serial.begin(9600);
  
  pinMode(9, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(7, OUTPUT);
  
  attachInterrupt(1, timercheck, FALLING);
  
  digitalWrite(9, 0);
  digitalWrite(8, 0);
  digitalWrite(7, 0);

  Timer1.initialize(1000);
  Timer1.attachInterrupt(miltimerF);
  
  all_off();
}

int pos = 0;

void loop() {
  if(nowPosition > nextPosition) {
    pos = (pos+1)%30;
    nextPosition += 12.0;
    show_bytes(pos, 2);
  }
}

void timercheck() {
  period = millis() - timerr;
  timerr = millis();
  nowPosition = 0.0;
  nextPosition = 12.0;
  omega = 360.0/(double(period));
}

void miltimerF() {
  nowPosition += omega;
  if(pos == 29) nowPosition += omega;
}
