void setup() {
  Serial.begin(9600);
  //pinMode(13, INPUT_PULLUP);
  pinMode(10, OUTPUT);
}
int toneperiod = 10, period = 100;
int timerr = 0;
boolean bools[1000];
int n = 0;
void loop() {
  bools[n] = digitalRead(6);
  if(n > 300) {
    if(bools[n] && (bools[n-period]  || bools[n-period-2] || bools[n-period+2] || bools[n-period - 1] || bools[n-period+1])) {
      Serial.println(bools[n]*5);
      tone(10, 100, toneperiod);
    }
    Serial.println(bools[n]);
    n = (n+1)%1000+110;
  }
  else n++;;
  delay(1);
}
