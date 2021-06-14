#define NUM_LEDS 92
#include "FastLED.h"
#define PIN 3
CRGB leds[NUM_LEDS];


int micDataLength = 5;
Queue micData(micDataLength), amplitudes(15);
float maxVolume = 1, minVolume = 0;

void setup() {
 Serial.begin(9600);
 pinMode(4, INPUT_PULLUP);
 pinMode(5, INPUT_PULLUP);

 FastLED.addLeds<WS2811, PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
 FastLED.setBrightness(255);
  
 micData.Fill(analogRead(A5));
 amplitudes.Fill(analogRead(A5));
}

float Hue = 0;
void loop() {
  if(micData.Full()) micData.deQueue();
  micData.enQueue(analogRead(A5));

  Queue bigMicData(micDataLength);
  float micAv = micData.average();
  float count = 0, sum;
  for(int i = 0; i < micDataLength; i++) {
    if(micData.myQueue[i] >= 3/2*micAv && micData.myQueue[i] != micData.emptyValue) {
      count++;
      sum += micData.myQueue[i];
    }
  }
  if(count > 0) {
    if(amplitudes.Full()) amplitudes.deQueue();
    amplitudes.enQueue(sum/count);
  }

  
  int Height = constrain(int(map(amplitudes.average(), 300, 500, 1, NUM_LEDS/2)), 0, NUM_LEDS);
  if(!amplitudes.Empty()) Serial.println(amplitudes.average());  
  for (int i = 0; i < NUM_LEDS; i++) {         // от 0 до первой трети
    if(!(i > NUM_LEDS/2+Height || i < NUM_LEDS/2-Height)) leds[i] = CHSV(int(Hue), 255, 150);
    else leds[i] = CHSV(0, 0, 0);
  }
  Hue = (Hue+0.5);
  if(Hue > 255) Hue = 0;
  FastLED.show();
}
