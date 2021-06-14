// пример с "бегущей радугой" для библиотеки FastLED
#define NUM_LEDS 98
#include "FastLED.h"
#define PIN 9
CRGB leds[NUM_LEDS];
byte counter;
int l = 2, offset = 0;
boolean flag = true;
void setup() {
  FastLED.addLeds<WS2811, PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(50);
  pinMode(13, OUTPUT);
}
long long colour = 0;
void loop() {
  for (int i = 0; i < NUM_LEDS; i++ ) {         // от 0 до первой трети
    if(i > -1) {
      leds[i*l] = CHSV(map(int(sin(colour*0.2)*100), 100, -100, 130, 160), 255, 255);
      leds[i*l+1] = CHSV(map(int(sin(colour*0.2)*100), 100, -100, 130, 160), 255, 255);
     //leds[i*l+2] = CHSV(map(int(sin(colour*0.4)*100), 100, -100, 130, 160), 255, 255);
     //leds[i*l+3] = CHSV(map(int(sin(colour*0.4)*100), 100, -100, 130, 160), 255, 255);
     //leds[i*l+4] = CHSV(map(int(sin(colour*0.4)*100), 100, -100, 130, 160), 255, 255);
    }
  colour++;
  }
  offset++;
  FastLED.show();
  delay(100);         // скорость движения радуги
}
//155 - синий
//125 - голубой
