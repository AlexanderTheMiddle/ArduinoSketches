#include <arduino-timer.h>
auto timer = timer_create_default();
long currentMillis = 0;
bool timerFunction(void *) {
  currentMillis+=1;
  return true; // repeat? true
}

#include <Servo.h>

Servo servos[4][3];
boolean reverse = false;
int servosPins[4][3] = {
  {2, 3, 4},
  {5, 6, 7},
  {8, 9, 10},
  {11, 12, A0},
};
int d = 30, dd = 50, ddd = 40;
int servosBoundary[4][3][2] = {
  {  {37+d, 176}, {180, 40}, {180, 0} },
  {  {134-d, 0}, {0, 140}, {3, 180} },
  {  {19, 165}, {172, 0}, {180, 15} },
  {  {162, 10}, {16, 180}, {7, 180} }
};


int unfoldingTargets[15][4][3] = {
  { {37+d, 180, 180}, {134-d, 0, 3}, {19, 172, 180}, {162, 16, 7} }, // all folded
  //{ {37+d, 180, 180}, {134-d, 0, 3}, {19, (servosBoundary[2][1][0]+servosBoundary[2][1][1])/2, 180}, {162, (servosBoundary[3][1][0]+servosBoundary[3][1][1])/2, 7} }, //  middle motors on all arms are in the middle positions
  { {37+d, (servosBoundary[0][1][0]+servosBoundary[0][1][1])/2, 180}, {134-d, (servosBoundary[1][1][0]+servosBoundary[1][1][1])/2, 3}, {19, (servosBoundary[2][1][0]+servosBoundary[2][1][1])/2, 180}, {162, (servosBoundary[3][1][0]+servosBoundary[3][1][1])/2, 7} }, //  middle motors on all arms are in the middle positions
  
  /*{ {47, (servosBoundary[0][1][0]+servosBoundary[0][1][1])/2, 180}, {134, (servosBoundary[1][1][0]+servosBoundary[1][1][1])/2, 3}, {165, 0, 15}, {10, 180, 180} }, // bottom legs go to the finish position, tops dont move
  { {57, (servosBoundary[0][1][0]+servosBoundary[0][1][1])/2, 180}, {134, (servosBoundary[1][1][0]+servosBoundary[1][1][1])/2, 3}, {165, 0, 15}, {10, 180, 180} }, // bottom legs go to the finish position, tops dont move
  { {67, (servosBoundary[0][1][0]+servosBoundary[0][1][1])/2, 180}, {134, (servosBoundary[1][1][0]+servosBoundary[1][1][1])/2, 3}, {165, 0, 15}, {10, 180, 180} }, // bottom legs go to the finish position, tops dont move
  { {77, (servosBoundary[0][1][0]+servosBoundary[0][1][1])/2, 180}, {134, (servosBoundary[1][1][0]+servosBoundary[1][1][1])/2, 3}, {165, 0, 15}, {10, 180, 180} }, // bottom legs go to the finish position, tops dont move
  { {87, (servosBoundary[0][1][0]+servosBoundary[0][1][1])/2, 180}, {134, (servosBoundary[1][1][0]+servosBoundary[1][1][1])/2, 3}, {165, 0, 15}, {10, 180, 180} }, // bottom legs go to the finish position, tops dont move
  { {97, (servosBoundary[0][1][0]+servosBoundary[0][1][1])/2, 180}, {134, (servosBoundary[1][1][0]+servosBoundary[1][1][1])/2, 3}, {165, 0, 15}, {10, 180, 180} }, // bottom legs go to the finish position, tops dont move
  { {107, (servosBoundary[0][1][0]+servosBoundary[0][1][1])/2, 180}, {134, (servosBoundary[1][1][0]+servosBoundary[1][1][1])/2, 3}, {165, 0, 15}, {10, 180, 180} }, // bottom legs go to the finish position, tops dont move
  { {117, (servosBoundary[0][1][0]+servosBoundary[0][1][1])/2, 180}, {134, (servosBoundary[1][1][0]+servosBoundary[1][1][1])/2, 3}, {165, 0, 15}, {10, 180, 180} }, // bottom legs go to the finish position, tops dont move
  { {127, (servosBoundary[0][1][0]+servosBoundary[0][1][1])/2, 180}, {134, (servosBoundary[1][1][0]+servosBoundary[1][1][1])/2, 3}, {165, 0, 15}, {10, 180, 180} }, // bottom legs go to the finish position, tops dont move
  { {137, (servosBoundary[0][1][0]+servosBoundary[0][1][1])/2, 180}, {134, (servosBoundary[1][1][0]+servosBoundary[1][1][1])/2, 3}, {165, 0, 15}, {10, 180, 180} }, // bottom legs go to the finish position, tops dont move
  { {147, (servosBoundary[0][1][0]+servosBoundary[0][1][1])/2, 180}, {134, (servosBoundary[1][1][0]+servosBoundary[1][1][1])/2, 3}, {165, 0, 15}, {10, 180, 180} }, // bottom legs go to the finish position, tops dont move
  { {157, (servosBoundary[0][1][0]+servosBoundary[0][1][1])/2, 180}, {134, (servosBoundary[1][1][0]+servosBoundary[1][1][1])/2, 3}, {165, 0, 15}, {10, 180, 180} } // bottom legs go to the finish position, tops dont move
  */
  
  
  
  
  
  { {37+d, (servosBoundary[0][1][0]+servosBoundary[0][1][1])/2, 180}, {134-d, (servosBoundary[1][1][0]+servosBoundary[1][1][1])/2, 3}, {165, 0, 15+40}, {10, 180, 180-40} },
  { {37+d, 150, 180}, {134-d, 30, 3}, {165, 0, 15+ddd}, {10, 180, 180-ddd} }, //  middle motors on all arms are in the middle positions
  
  { {175, 40+dd, 1+ddd}, {1, 140-dd, 179-ddd}, {164, 1+dd, 16+ddd}, {11, 179-dd, 179-ddd} } // all unfolded
  //{ {100, 70, 70}, {70, 100, 100}, {100, 70, 70}, {70, 100, 100} }
}; 
 
int servosPosition[4][3];
int servosTarget[4][3];
int fromLastStep[4][3];
boolean onTarget[4][3];

int stepLength = 50;

void setup() {
  Serial.begin(9600);
  pinMode(A3, INPUT_PULLUP);
  timer.every(1, timerFunction);
  
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      servos[i][j].attach(servosPins[i][j]);
      servos[i][j].write(servosBoundary[i][j][0]);
      servosTarget[i][j] = servosBoundary[i][j][0];
      servosPosition[i][j] = servosBoundary[i][j][0];
      onTarget[i][j] = true;
      fromLastStep[i][j] = currentMillis;
    }
  }
  while(digitalRead(A3));
}

int stepN = 0;
void loop() {

unfoldingTargets[4][0][0] = 175;
unfoldingTargets[4][0][1] = 40+dd;
unfoldingTargets[4][0][2] = 1+ddd;

unfoldingTargets[4][1][0] = 1;
unfoldingTargets[4][1][1] = 140-dd;
unfoldingTargets[4][1][2] = 179-ddd;

unfoldingTargets[4][2][0] = 164;
unfoldingTargets[4][2][1] = 1+dd;
unfoldingTargets[4][2][2] = 16+ddd;

unfoldingTargets[4][3][0] = 11;
unfoldingTargets[4][3][1] = 179-dd;
unfoldingTargets[4][3][2] = 179-ddd;
/*
  unfoldingTargets[4][0][] = {
  { {175, 40+dd, 1+ddd}, {1, 140-dd, 179-ddd}, {164, 1+dd, 16+ddd}, {11, 179-dd, 179-ddd} } // all unfolded
  //{ {100, 70, 70}, {70, 100, 100}, {100, 70, 70}, {70, 100, 100} }
}; 
*/



  dd = map(analogRead(A4), 0, 1023, 30, 70);
  ddd = map(analogRead(A5), 0, 1023, 20, 60);
  timer.tick();

  //saying that all of the servos are off targets
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 3; j++) {
      onTarget[i][j] = false;
    }
  }
  
  //choosing targets
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 3; j++) {
      servosTarget[i][j] = unfoldingTargets[stepN][i][j];
    }
  }
  
  //calculating new positions
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 3; j++) {
      if(currentMillis - fromLastStep[i][j] > stepLength) {
        servosPosition[i][j]+=sgn(servosTarget[i][j] - servosPosition[i][j]);
        onTarget[i][j] = (servosPosition[i][j] == servosTarget[i][j]);
        fromLastStep[i][j] = currentMillis;
      }
    }
  }

  //moving to new positions
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 3; j++) {
      servos[i][j].write(servosPosition[i][j]);
    }
  }

  if(productOnTarget()) stepN = min(stepN+1, 4);
}
