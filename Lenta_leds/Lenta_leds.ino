#define NUM_LEDS 4
#include "FastLED.h"
#define PIN 14
CRGB leds[NUM_LEDS];

void setup() {
  pinMode(A0, OUTPUT);
  digitalWrite(A0, HIGH);
  FastLED.addLeds<WS2811, PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(100);
  pinMode(13, OUTPUT);
for (int i = 0; i < NUM_LEDS; i++ ) {         // от 0 до первой трети
    leds[i] = CHSV(255, 235, 225);  // HSV. Увеличивать HUE (цвет)
    // умножение i уменьшает шаг радуги
  }
       // counter меняется от 0 до 255 (тип данных byte)
  FastLED.show();
  delay(5);         // скорость движения радуги
}
void loop() {
  
  
}
//255, 235, 225 - red   255, 220, 255 ---
//90, 255, 230 - green
//60, 220, 255 - yellow - 10, 255, 225
//160, 200, 230 - blue


//255, 210, 200
// 0 255 255 orange
