#define NUM_LEDS 4
#include "FastLED.h"
#define PIN 14
CRGB leds[NUM_LEDS];
byte counter;
void setup() {
  FastLED.addLeds<WS2811, PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(100);
  pinMode(13, OUTPUT);
  pinMode(A2, OUTPUT);
  digitalWrite(A2, HIGH);
}
int ilast = 0;
int ilast2 = 0;
int icount = 0;
void loop() {
  digitalWrite(A2, LOW);
  int i = myrandom();
  digitalWrite(A2, HIGH);
  delayMicroseconds(100);
    if (i != ilast2) {
      if (i == ilast) icount++;
      if (i != ilast || i == ilast && icount % 2 == 0) {
        leds[i] = CHSV(90, 255, 230);
      
    FastLED.show();
    delay(400);
    leds[i] = CHSV(0, 0, 0);
    FastLED.show();
    delay(400);
    ilast2 = ilast;
    ilast = i;
    }
    }
}

int myrandom() {
  pinMode(A2, INPUT);
  int ran = analogRead(A2) % 4;
  pinMode(A2, OUTPUT);
  return ran;
}
//255, 235, 225 - red
//90, 255, 230 - green
//60, 220, 255 - yellow
//160, 200, 230 - blue
