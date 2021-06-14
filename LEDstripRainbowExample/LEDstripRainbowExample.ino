
// пример с "бегущей радугой" для библиотеки FastLED
#define NUM_LEDS 6
//#include "FastLED.h"
#define PIN 3
//CRGB leds[NUM_LEDS];
byte counter;
void setup() {
  //FastLED.addLeds<WS2811, PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  //FastLED.setBrightness(20);
 // pinMode(PIN, OUTPUT);
}
void loop() {
  for (int i = 0; i < NUM_LEDS; i++ ) {         // от 0 до первой трети
     //leds[i] = CHSV(counter + i, 255, 255);  // HSV. Увеличивать HUE (цвет) leds[i] = CHSV(counter + i * 2, 255, 255);  // HSV. Увеличивать HUE (цвет)
     // умножение i уменьшает шаг радуги
  }
  counter++;        // counter меняется от 0 до 255 (тип данных byte)
  //FastLED.show();
  delay(5);         // скорость движения радуги
}
