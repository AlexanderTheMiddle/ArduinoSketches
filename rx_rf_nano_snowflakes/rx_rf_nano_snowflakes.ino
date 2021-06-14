
#include <TimerOne.h>

#define NUM_LEDS 15
#include "FastLED.h"
#define PIN 6
CRGB leds[NUM_LEDS];

int state[40], target[40], changeStep[40], ONnumber = 10, shiningPeriod = 4000000, topPeriod = 10000000, quietPeriod = 5000000;
int shiningStep = shiningPeriod / (255 * 2);
int minBr = 0, maxBr = 255, fasterBefore = 80, appearingProbability = 1000;
boolean isMin[40], isMax[40], isON[40];
long nowMicros = 0, lastTimeChanged[40];


//Receiver program
#include <SPI.h>
#include "Mirf.h"
#include "nRF24L01.h"
#include "MirfHardwareSpiDriver.h"
Nrf24l Mirf = Nrf24l(10, 9);

byte info[5];

void setup()
{
  Serial.begin(9600);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();

  Mirf.setRADDR((byte *)"LOLOL"); //Set your own address (receiver address) using 5 characters
  Mirf.payload = sizeof(info);
  Mirf.channel = 90;             //Set the used channel
  Mirf.config();
  Serial.println("Listening...");  //Start listening to received data





  //Serial.begin(9600);
  FastLED.addLeds<WS2811, PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(100);
  Timer1.initialize(100);
  Timer1.attachInterrupt(timerFunction);
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

int potx, poty, buttonNow = 0, buttonWas = 0;
boolean regularMode = true;

void loop() {
  //rf loop
  if (Mirf.dataReady()) { //When the program is received, the received data is output from the serial port
    Mirf.getData((byte *) &info);
  }
  
    potx = info[0]*255 + info[1];
    poty = info[2]*255 + info[3];
    buttonNow = info[4];

  //changing variables
   ONnumber = map(potx, 0, 1023, 0, NUM_LEDS-2);
   appearingProbability = map(poty, 0, 1023, 10, 5000);
   Serial.print(ONnumber);
   Serial.print(" ");
   Serial.println(appearingProbability);
  //strip loop
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

      if (!isMin[i] && !isMax[i] && (nowMicros - lastTimeChanged[i] > shiningStep)) {
        state[i] += changeStep[i];
        lastTimeChanged[i] = nowMicros;
      }
      else if (isMax[i] && nowMicros - lastTimeChanged[i] > topPeriod) {
        state[i] += changeStep[i];
        lastTimeChanged[i] = nowMicros;
        //Serial.print("MAXING ");
      }
      else if (isMin[i] && nowMicros - lastTimeChanged[i] > quietPeriod ) {
        //Serial.print("OFFING ");
        isON[i] = false;
      }
    }

    //allowing to be on
    for (int j = 0; j < ONnumber - amountOfON(); j++) {
      if (random(0, appearingProbability) < 1) {
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
  
  buttonWas = buttonNow;
  
}
