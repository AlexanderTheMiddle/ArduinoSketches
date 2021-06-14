

#define NUM_LEDS 10
#include "FastLED.h"
#define PIN 6
CRGB leds[NUM_LEDS];

int state[40], target[40], changeStep[40], ONnumber = 5, shiningPeriod = 4000000, topPeriod = 10000000, quietPeriod = 5000000;
int shiningStep = shiningPeriod / (255 * 2);
int minBr = 0, maxBr = 255, fasterBefore = 80;
boolean isMin[40], isMax[40], isON[40];
long nowMicros = 0, lastTimeChanged[40];
void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2811, PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(50);

  for (int i = 0; i < 40; i++) {
    state[i] = minBr;
    target[i] = 0;
    lastTimeChanged[i] = 0;
    changeStep[i] = 1;
    isMin[i] = true;
    isMax[i] = false;
    isON[i] = false;
  }
}


void loop() {



  for (int i = 0; i < NUM_LEDS; i++) {
    if (isON[i]) {

      //setting boolean variables and  changeStep
      if (state[i] <= minBr) {
        isMin[i] = true;
        changeStep[i] = 1;
      }
      else {
        isMin[i] = false;
        if (state[i] >= maxBr) {
          isMax[i] = true;
          changeStep[i] = -1;
        }
        else isMax[i] = false;
      }
      //if (state[i] < fasterBefore) changeStep[i] *= 2;

      //changing values
      //Serial.print((nowMicros - lastTimeChanged[i]));
      //Serial.print(" ");

      /*
        for (int i = 0; i < NUM_LEDS; i++) {
        Serial.print(isMax[i]);
        Serial.print(" ");
        }
        Serial.println("");
      */

      if (!isMin[i] && !isMax[i] && (micros() - lastTimeChanged[i] > shiningStep)) {
        state[i] += changeStep[i];
        lastTimeChanged[i] = micros();
      }
      else if (isMax[i] && (micros() - lastTimeChanged[i] > topPeriod)) {
        state[i] += changeStep[i];
        lastTimeChanged[i] = nowMicros;
        //Serial.print("MAXING ");
      }
      else if (isMin[i] && (micros() - lastTimeChanged[i] > quietPeriod)) {
        //Serial.print("OFFING ");
        isON[i] = false;
      }
    }

    //allowing to be on
    for (int j = 0; j < ONnumber - amountOfON(); j++) {
      if (random(0, 1000) < 1) {
        int index = int((analogRead(A0) * (millis() + 59)) % NUM_LEDS);
        while (isON[index]) index = int((analogRead(A0) * (millis() + 59)) % NUM_LEDS);
        isON[index] = true;
        state[i] = minBr + 1;
      }
    }

    if (isON[i]) {
      leds[i] = CHSV(0, 0, constrain(state[i], minBr, maxBr));
    }
    else leds[i] = CHSV(0, 0, 0);
  }

  FastLED.show();


}


/*
  Variables to adjust to get different results:

  topPeriod
  shiningPeriod
  ONnumber

  (brightness also, but like beforehand // or maxbr);

*/

int amountOfON() {
  int sum = 0;
  for (int i = 0; i < NUM_LEDS; i++) {
    if(isON[i]) sum++;
  }
  return sum;
}
