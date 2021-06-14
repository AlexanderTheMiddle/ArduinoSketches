#include <arduino-timer.h>
#include <Servo.h>

Servo motor;

int nowPosition = 180;
int target = 0;
int stepLength = 50;
long currentMillis = 0;
long fromLastStep = 0;
auto timer = timer_create_default();

bool timerFunction(void *) {
  currentMillis+=1;
  return true; // repeat? true
}

void setup() {
  Serial.begin(9600);
  
  timer.every(1, timerFunction);
  
  motor.attach(A2);
  motor.write(nowPosition);
  delay(100);
}

int counter = 0;
void loop() {
  timer.tick(); // tick the timer
  if(currentMillis - fromLastStep > stepLength) {
    nowPosition+=sgn(target - nowPosition);
    fromLastStep = currentMillis;
  }
  motor.write(nowPosition);
}

int sgn(int a) {
  if(a < 0) return -1;
  else if(a == 0) return 0;
  else return 1;
}
