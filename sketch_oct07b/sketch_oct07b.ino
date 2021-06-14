void setup() {
  Serial.begin(9600);
  pinMode(5, INPUT_PULLUP);

}

//might change

int changes[300];
int period = 100;
int jumpPeriod = 5;



boolean input = false, lastInput = false;
boolean jump = false;

int sums[100], maxx = 0, band = 1;
int values[20];
int i = 0;
float sped;

void loop() {
  input = !digitalRead(5);
  values[0] = input;
  changes[0] = int(input != lastInput);
  if(input == 0) {
    jump = false;
  }
  if(sum(values, jumpPeriod) == jumpPeriod) {
    jump = true;
  }
  sums[0] = sum(changes, period);
  Serial.print(average(band, sums));
  Serial.print(',');
  if(average(band, sums) > maxx) maxx = average(band, sums);
  Serial.print(maxx);
  //Serial.print(',');
  //Serial.print(sum(values, jumpPeriod));
  //if(jump)Serial.print("jump");
  Serial.println("");
  lastInput = input;
  i++;
  push(changes, 298);
  push(values, 20);
  push(sums, 100);
  delay(10);
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
