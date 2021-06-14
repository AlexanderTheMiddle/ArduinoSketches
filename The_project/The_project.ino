#include <LowPower.h>

#define detector_pin 5
#define detector_power 6
#define pump 7

void setup() {
  pinMode(detector_power, OUTPUT);
  pinMode(pump, OUTPUT);
}

int period = 1;
void loop() {
  digitalWrite(detector_power, HIGH);
  delay(5);
  if(digitalRead(detector_pin)) {
    digitalWrite(pump, HIGH);
    while(digitalRead(detector_pin)) { }
    digitalWrite(pump, LOW);
    delay(3000);
  }
  if(digitalRead(detector_pin)) {
    digitalWrite(pump, HIGH);
    while(digitalRead(detector_pin)) { }
    digitalWrite(pump, LOW);
  }
  digitalWrite(detector_power, LOW);
  for(int i = 0; i < period; i++) {
    LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
  }
}
