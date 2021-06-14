int LEDpins[2] = {15, 14};
int MAGNETpins[2] = {10, 16};

void setup() {
  Serial.begin(9600);
  
  pinMode(MAGNETpins[0], OUTPUT);
  pinMode(MAGNETpins[1], OUTPUT);
  pinMode(LEDpins[0], OUTPUT);
  pinMode(LEDpins[1], OUTPUT);
  digitalWrite(LEDpins[1], LOW);


}
boolean LEDstate = false, MAGNETstate = false;
long LEDt = 0, MAGNETt = 0, out = 0, LEDduration = 200, LEDspacing = 0, MAGNETperiod = 6000;
//200-250 мкс на магнит
//4000-5000 мкс на магнит
void loop() {
  //LEDduration = 1*map(analogRead(0), 1023, 0, 200, 600);
  LEDspacing = int(map(analogRead(A2), 0, 1023, 11000, 13000));

  if(micros() - MAGNETt > MAGNETperiod) {
    MAGNETt = micros();
    MAGNETstate = !MAGNETstate;
    digitalWrite(MAGNETpins[0], MAGNETstate);
    digitalWrite(MAGNETpins[1], !MAGNETstate);
  }
  
  if(LEDstate && micros() - LEDt > LEDduration) {
    LEDt = micros();
    LEDstate = !LEDstate;
    digitalWrite(LEDpins[0], LEDstate);
  }
  
  else if(!LEDstate && micros() - LEDt > LEDspacing) {
    LEDt = micros();
    LEDstate = !LEDstate;
    digitalWrite(LEDpins[0], LEDstate);
  }

  if(micros() - out > 500000) {
    out = micros();
    Serial.print(LEDduration);
    Serial.print("        ");
    Serial.println(LEDspacing);
  }

}
