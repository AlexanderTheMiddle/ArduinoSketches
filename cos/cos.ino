#include <Servo.h>
Servo a[8];
int ii[8] = {3, 4, 5, 6, 7, A3, A4, A5}; 
void setup() {
  Serial.begin(9600);
  for(int i = 0; i < 8; i++) {
    a[i].attach(ii[i]);
  }
  for(int i = 0; i < 8; i++) {
    a[i].write(90);
  }
  a[4].write(0);
  a[7].write(120);
}

double Dmax = 15, Tmin = 70, Tmax = 150;
int D = 10;
void loop() {
  for(double Talpha = Tmin; Talpha < Tmax + 1; Talpha++) {
    a[7].write(Talpha);
    delay(int(Dmax*(abs(cos(0.0175* (Talpha - Tmin)/(Tmax - Tmin))))));
  }
  delay(D);
  for(double Talpha = Tmax; Talpha > Tmin - 1; Talpha--) {
    a[7].write(int(Talpha));
    delay(int(Dmax*(abs(cos(0.0175* (Talpha - Tmin)/(Tmax - Tmin))))));
  }
  delay(D);
 
}
