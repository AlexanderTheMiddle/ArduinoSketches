/*
void setup() {
  Serial.begin(9600);
  pinMode(5, INPUT_PULLUP);

}
boolean input = false, lastInput = false;
int changes[500];
int i = 0, period = 100;
float sped;
void loop() {
  input = int(!digitalRead(5));
  changes[0] = int(input != lastInput);
  Serial.println(sum());
  lastInput = input;
  i++;
  push();
  delay(2);
}

int sum() {
  int summ = 0;
  for(int j = 0; j < period; j++) {
    summ += changes[j];
  }
  return summ;
}

void push() {
  for(int j = period; j > -1; j--) {
    changes[j+1] = changes[j];
  }
}

*/
int pins[2] = {3, 2};
int LEDpins[2] = {5, 9};

 void setup() {
  Serial.begin(9600);
  pinMode(pins[0], INPUT_PULLUP);
  pinMode(pins[1], INPUT_PULLUP);
  pinMode(LEDpins[0], OUTPUT);
  pinMode(LEDpins[1], OUTPUT);

}

//might change

int changes[2][200], values[2][60];
int jumpPeriod = 30;
int period = 150;
int jumpDuration = 10, fromJump[2] = { 0, 0};



boolean input[2] = {false, false}, lastInput[2] = {false, false};
boolean jump[2] = {false, false};
int sums[2][100], band = 2;
int JUMPSUM[2] = {0, 0};
int i[2] = {0, 0};
float sped;

void loop() {
  for(int ii = 0; ii < 2; ii++) {
  input[ii] = !digitalRead(pins[ii]);
  digitalWrite(LEDpins[ii], input[ii]);
  //values[0] = input;
  if(input[ii]) JUMPSUM[ii] = constrain(JUMPSUM[ii]+1, 0, jumpPeriod);
  else JUMPSUM[ii] = 0;
  changes[ii][0] = int(input[ii] != lastInput[ii]);
  if(fromJump[ii] == jumpDuration && jump[ii]) {
    jump[ii] = false;
  }
  else if (jump) {
    fromJump[ii]++;
  }
  if(JUMPSUM[ii] >= jumpPeriod - 1) {
    jump[ii] = true;
    fromJump[ii] = 0;
  }
  sums[ii][0] = sum(changes[ii], period);

  lastInput[ii] = input[ii];
  i[ii]++;
  push(changes[ii], 198);
  push(sums[ii], 98);
  push(values[ii], 17);
  }

  //for arduino testing
  /*
   /Serial.print(JUMPSUM);
  Serial.print(",");
  Serial.println(input);
  */
  
  //for processing:
  Serial.print(int(average(band, sums[0])));
  Serial.print(",");
  Serial.print(int(jump[0]));
  Serial.print(",");
  Serial.print(int(average(band, sums[1])));
  Serial.print(",");
  Serial.print(int(jump[1]));
  Serial.println(",");
    //Serial.println(!digitalRead(pins[0]));

  
  delay(5);
}

float average(int n, int a[]) {
  float av = 0;
  for(int j = 0; j < n; j++) {
    av+=a[j];
  }
  return av/n;
  
}

int sum(int a[], int p) {
  int summ = 0;
  for(int j = 0; j < p; j++) {
    summ += a[j];
  }
  return summ;
}

void push(int a[], int p) {
  for(int j = p; j > -1; j--) {
    a[j+1] = a[j];
  }
}
