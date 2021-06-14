#include <Servo.h>
#include <String.h>
int pins[10] = {3, 4, 5, 6, 7, 8, 9, 10, 11, 12}, state[10], target[10];
long fromlaststep[10], steps[10]= {0, 1, 1, 0, 0, 0, 0, 0, 0, 0};
long tim[10], period[10];
//________________рот____Хглаз____Углаз___Хголова____Уголова_____хвост_____шея______-1______левая_____правая___
int start[10] = { 40,      0,     30,       0,         10,        0,      50,      -1,      100,       35};
int finish[10] = { 180,    90,    140,     180,        130,       140,     130,     -1,      145,       60};
int N = 10;
int randoms[10][15];
boolean targetgot[10];
Servo a[10];
void setup() {
  Serial.begin(9600);
  for(int i = 0; i < N; i++) {
    a[i].attach(pins[i]);
  }
  for(int i = 0; i < N; i++) {
    if(i != 7) target[i] = (start[i] + finish[i])/2;
    else if(i == 7) target[7] = 180 - state[6];
    state[i] = target[i];
    targetgot[i] = 1;
  }
  state[4] = 20;
  for(int i = 0; i < N; i++) {
    a[i].write(state[i]);
  }
  

  ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
 target[5] = start[5]; // можешь сделать рандом выбор старт или финиш
 //while(1) a[5].write(90);
}


int aa = 0, bb = 200;
int p1 = 250, p2 = 2000;
int qwertyuio[7] = {1, 2, 5, 6, 7, 8, 9}, i;
double Dmax = 2, k = 0.3;


void loop() {
  Serial.println(long(millis()));
  for(int q = 0; q < 7; q++) {
    i = qwertyuio[q];
    if(long(millis()) - tim[i] >= period[i] && targetgot[i]) {
      tim[i] = long(millis());
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////targets
      if(i == 1) {
        target[1] = random(start[i], finish[i]);////////////для глаз сразу пишем state чтобы они сразу перемещались на нужные позиции
        state[i] = target[i];
      }
      if(i == 2) {
        target[2] = random(start[i], finish[i]);
        state[i] = target[i];
      }
      if(i == 5) {
        if(target[5] == start[5]) target[5] = finish[5];
        else if(target[5] == finish[5]) target[5] = start[5];
      }
      if(i == 6) target[6] = random(55, 70);
      if(i == 7) target[7] = 180 - target[6];
      if(i == 8 || i == 9) target[i] = random(start[i], finish[i]);
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////periods
      if(i == 1) period[1] = random(p1, p2);
      if(i == 2) period[2] = period[1];
      if(i == 5) period[5] = 0;
      if(i == 6) period[6] = random(p1, p2);
      if(i == 7) period[7] = period[6];
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////steps
      if(i == 1) steps[1] = aa;
      if(i == 2) steps[2] = aa;
      if(i == 5) steps[i] = int(Dmax*(1.0 - k*sin(0.0175*180* (state[i] - start[i])/(finish[i] - start[i]))));
      if(i == 6) steps[6] = bb;
      if(i == 7) steps[7] = bb;
      if(i == 8 || i == 9) steps[i] = 70;
      ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////targetgot = 0
      targetgot[i] = 0;
    }
    if(state[i] != target[i] && long(millis()) - fromlaststep[i] > steps[i]) {
      fromlaststep[i] = long(millis());
      state[i] += (0.5 - (state[i] > target[i]))*2;
    }
    else if(state[i] == target[i]) targetgot[i] = 1;
    a[i].write(state[i]);
  }
}
