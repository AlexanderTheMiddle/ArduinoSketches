


#define NUM_LEDS 180
#include "FastLED.h"
#define PIN 7
CRGB leds[NUM_LEDS];
//byte counter;
void setup() {
  FastLED.addLeds<WS2811, PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(100);
  pinMode(7, OUTPUT);
}
int last = 0;
void loop() {
  int n = int(map(analogRead(A0), 0, 1024, 0, NUM_LEDS));
  
  int brt;
  //for (int i = 0; i < NUM_LEDS; i++ ) {    
  //  if(i < n - 7 || i > n + 7) leds[i] = CHSV(0, 0, 0); 
  //}
  if (n != last) {
    for(int i = -2; i < 3 ; i++) {
      leds[last + i] = CHSV(0, 0, 0);
    }
  }
  //for (int i = 0; i < 7; i++ ) { 
  //  brt = 81 + 25 * (i+1);   
  //  leds[i + n - 7] = CHSV(brt, brt, brt);
  //}
  //leds[n - 2] = CHSV(150, 150, 150);
  //leds[n - 1] = CHSV(200, 200, 200);
  //leds[n] = CHSV(255, 255, 255);
  //leds[n + 1] = CHSV(200, 200, 200);
  //leds[n + 2] = CHSV(150, 150, 150);

    for(int i = -5; i < 0 ; i++) {
      brt = 255 + 25*i;
      //brt = 255;
      leds[n + i] = CHSV(brt, brt, brt);
    }
    for(int i = 5; i < 0 ; i++) {
      brt = 255 - 25*i;
      //brt = 255;
      leds[n + i] = CHSV(brt, brt, brt);
    }

  
  
  //for (int i = 0; i < 7; i-- ) { 
  //  brt = 81 + 25* (i+1);
  //  leds[ n + 7 - i] = CHSV(brt, brt, brt);
  //}
  //CHSV(brt, brt, brt);
  FastLED.show();
  delay(1);         // скорость движения радуги
  last = n;
}
