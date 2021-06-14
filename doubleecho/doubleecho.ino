#include <TimerOne.h>

long currentTime;
int numberOfPoints = 1;
int echoPins[4] = {7, 5, 4, 3};
int pingPins[4] = {8, 6, 4, 3};
float coord[4][3];
boolean recieved[4] = {false, false, false, false};

void setup() {
   Serial.begin(9600);

   for(int i = 0; i < numberOfPoints+1; i++) {
     pinMode(pingPins[i], OUTPUT);
     digitalWrite(pingPins[i], LOW);
     pinMode(echoPins[i], INPUT);
   }
   
   //Timer1.initialize(1); // set a timer of length 100000 microseconds (or 0.1 sec - or 10Hz => the led will blink 5 times, 5 cycles of on-and-off, per second)
   //Timer1.attachInterrupt( timerFunction ); // attach the service routine here
}

long duration[4], l[4];
void loop() {
  for(int i = 1; i < numberOfPoints+1; i++) {
    digitalWrite(pingPins[i], HIGH);
  }
   currentTime = micros();
   delayMicroseconds(10);
   for(int i = 1; i < numberOfPoints+1; i++) {
     digitalWrite(pingPins[i], LOW);
   }

   while(!recieved[0] && micros() - currentTime < 8000) {
    if(digitalRead(echoPins[0])) {
      duration[0] = micros() - currentTime;
      recieved[0] = true;
    }
   }
   Serial.print(microsecondsToCentimeters(duration[0]));
   //Serial.print(currentTime);
   Serial.print(" cm");
   Serial.println();

   recieved[0] = false;
   //delay(100);
}

long microsecondsToInches(long microseconds) {
   return microseconds / 74;
}

long microsecondsToCentimeters(long microseconds) {
   return microseconds / 29;
}

/*
void timerFunction() {
  currentTime+=1;
  //if(currentTime %10000 == 0)Serial.println(currentTime);
}
*/
