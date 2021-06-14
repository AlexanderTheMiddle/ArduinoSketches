#define trigger 4
#define echo A0
#define vibr 11
//10
void setup() {
  Serial.begin(9600);
  pinMode(trigger, OUTPUT);
  pinMode(vibr, OUTPUT);
  pinMode(echo, INPUT);
  digitalWrite(trigger, LOW);
  delay(10);
}

void loop() {
  long duration, sm;
  digitalWrite(trigger, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger, LOW);
  duration = pulseIn(echo, HIGH);
  sm = duration / 58;
  if (sm > 153) sm = 153;
  analogWrite(vibr, 153 - sm);
  Serial.print("Time (in microseconds): ");
  Serial.print(duration);
  Serial.print(" Santimeters: ");
  Serial.println(sm);
  //if (sm < 160) tone(10, 3500, 100);
  delay(1);
}
