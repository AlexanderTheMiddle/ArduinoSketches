#define NUM_LEDS 15
unsigned char SYM[47];

#include "FastLED.h"
#include <TimerOne.h>
#include <NewPing.h>

#define PIN 10
#define ECHO 5
#define TRIG 6
NewPing sonar(TRIG, ECHO, 400);


int lightSpotWidth = 1;

CRGB leds[NUM_LEDS];
byte counter;

float dist_3[3] = {0.0, 0.0, 0.0};   // массив для хранения трёх последних измерений
float middle, dist, dist_filtered;
float k;
byte i, delta;
unsigned long dispIsrTimer, sensTimer;


void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2811, PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(250);
  pinMode(PIN, OUTPUT);
}

void loop() {
  if (millis() - sensTimer > 50) {                          // измерение и вывод каждые 50 мс
    if (i > 1) i = 0;
    else i++;

    dist_3[i] = (float)sonar.ping() / 57.5;                 // получить расстояние в текущую ячейку массива

    dist = middle_of_3(dist_3[0], dist_3[1], dist_3[2]);    // фильтровать медианным фильтром из 3ёх последних измерений

    delta = abs(dist_filtered - dist);                      // расчёт изменения с предыдущим
    if (delta > 1) k = 0.7;                                 // если большое - резкий коэффициент
    else k = 0.1;                                           // если маленькое - плавный коэффициент

    dist_filtered = dist * k + dist_filtered * (1 - k);     // фильтр "бегущее среднее"
    Serial.println(dist_filtered);// вывести
    sensTimer = millis();                                   // сбросить таймер
  }

  if (micros() - dispIsrTimer > 300) {       // таймер динамической индикации (по-русски: КОСТЫЛЬ!)
    dispIsrTimer = micros();                 // сбросить таймер
  }



  
  //int centerIndex = map(analogRead(0), 0, 1023, lightSpotWidth/2 + 1, NUM_LEDS - lightSpotWidth/2 - 1);
  int centerIndex =constrain(int(dist_filtered/2.0), lightSpotWidth/2+1, NUM_LEDS-lightSpotWidth/2-1);
  for (int i = 0; i < NUM_LEDS; i++ ) {         // от 0 до первой трети
    int k = (abs(centerIndex - i)+2);
    //k*=k;
    if(abs(centerIndex - i) < lightSpotWidth/2 + 1) leds[i] = CHSV(255/k, 255/k, 255/k);
    else leds[i] = CHSV(0, 0, 0);
  }
  counter++;
  FastLED.show();
  delay(5);
}



float middle_of_3(float a, float b, float c) {
  if ((a <= b) && (a <= c)) {
    middle = (b <= c) ? b : c;
  }
  else {
    if ((b <= a) && (b <= c)) {
      middle = (a <= c) ? a : c;
    }
    else {
      middle = (a <= b) ? a : b;
    }
  }
  return middle;
}
