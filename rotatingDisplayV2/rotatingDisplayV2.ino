#include "FastLED.h"
#define NUM_LEDS 41
#define LEDPin 5
#define interruptPin 2

CRGB leds[NUM_LEDS];

boolean usingMillis = false;
float counter = 0;
volatile long halfPeriod = 1, lastHalfRevolutionTime = 0, minHalfPeriod = 100;
volatile boolean flip = false;
volatile float angleNow = 0;

// 12  12  4
byte LEDdata[12][12][4] = {
{{0,0,0,0},{0,239,6,6},{24,253,6,6},{49,254,6,6},{74,248,6,6},{98,0,0,0},{123,0,0,0},{148,0,0,0},{172,248,6,6},{197,254,6,6},{222,253,6,6},{246,239,6,6}},
{{0,252,6,6},{0,255,7,7},{30,255,7,7},{60,255,7,7},{90,251,6,6},{120,0,0,0},{151,251,6,6},{181,255,7,7},{211,255,7,7},{241,255,7,7},{0,0,0,0},{0,0,0,0}},
{{0,255,7,7},{0,255,7,7},{39,255,7,7},{78,255,7,7},{117,242,6,6},{156,255,7,7},{195,255,7,7},{234,255,7,7},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}},
{{0,255,7,7},{0,255,7,7},{55,255,7,7},{110,255,7,7},{165,255,7,7},{220,255,7,7},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}},
{{0,255,7,7},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}},
{{0,255,7,7},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}},
{{0,255,7,7},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}},
{{0,255,7,7},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}},
{{0,255,7,7},{0,255,7,7},{55,255,7,7},{110,255,7,7},{165,255,7,7},{220,255,7,7},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}},
{{0,255,7,7},{0,254,6,6},{39,248,6,6},{78,252,6,6},{117,255,7,7},{156,252,6,6},{195,248,6,6},{234,254,6,6},{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}},
{{0,252,6,6},{0,0,0,0},{30,0,0,0},{60,0,0,0},{90,0,0,0},{120,249,6,6},{151,0,0,0},{181,0,0,0},{211,0,0,0},{241,0,0,0},{0,0,0,0},{0,0,0,0}},
{{0,0,0,0},{0,0,0,0},{24,0,0,0},{49,0,0,0},{74,0,0,0},{98,0,0,0},{123,0,0,0},{148,0,0,0},{172,0,0,0},{197,0,0,0},{222,0,0,0},{246,0,0,0}}
};



void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2811, LEDPin, RGB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(50);
  pinMode(2, INPUT_PULLUP);
  attachInterrupt(3-interruptPin, interruptFunction, FALLING);

  if(!usingMillis) minHalfPeriod *= 1000;
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, 0, 0);
  }
}

void loop() {
  for(int i = 0; i < NUM_LEDS; i++) {
    leds[i] = CRGB(0, 0, 0);
  }
  
  angleNow = float(timeFunction() - lastHalfRevolutionTime)/float(halfPeriod)*PI;

  if(angleNow >= PI) {
    halfPeriod = timeFunction() - lastHalfRevolutionTime;
    lastHalfRevolutionTime = timeFunction();
    angleNow -= PI;
    flip = !flip;
  }
  
  for (int i = 0; i < NUM_LEDS; i++ ) {
    int Jindex = 0;
    for(int j = 0; float(LEDdata[i][j][0]) < angleNow*255.0/PI && j < sizeof(LEDdata[0])/sizeof(LEDdata[0][0]); j++) {
      Jindex = j;
    }
    int ledIndex = i;
    if(flip) ledIndex = NUM_LEDS - i - 1;
    leds[ledIndex] = CRGB(LEDdata[i][Jindex][2], LEDdata[i][Jindex][1], LEDdata[i][Jindex][3]);
  }

  FastLED.show();

}

long timeFunction() {
  if(usingMillis) return millis();
  else return micros();
}

void interruptFunction() {
  if(timeFunction() - lastHalfRevolutionTime > minHalfPeriod) {
    halfPeriod = timeFunction() - lastHalfRevolutionTime;
    lastHalfRevolutionTime = timeFunction();
    angleNow = 0;
    flip = false;
  }
}
