#include <Servo.h>

Servo servos[1][3];

int armNum = 1;
int servoPins[1][3] = {{10, 11, 12}};
int buttons[1][3][2] = {{{3, 4}, {5, 6}, {7, 8}}};
int pots[3] = {A2, A1, A0};

int servoMiddle[1][3] = {{78, 92, 92}};

void setup() {
  Serial.begin(9600);
  for(int i = 0; i < armNum; i++) {
    for(int j = 0; j < 3; j++) {
      for(int q = 0; q < 2; q++) {
        pinMode(buttons[i][j][q], INPUT_PULLUP);
      }
    }
  }
  for(int i = 0; i < armNum; i++) {
    for(int j = 0; j < 3; j++) {
      servos[i][j].attach(servoPins[i][j]);
    }
  }
  

}

void loop() {
  for(int i = 0; i < armNum; i++) {
    for(int j = 0; j < 3; j++) {
      boolean none = true;
      for(int q = 0; q < 2; q++) {
        if(!digitalRead(buttons[i][j][q])) {
          servos[i][j].write(180*q);
          none = false;
        }
      }
      if(none) servos[i][j].write(servoMiddle[i][j]);
    }
  }
}
