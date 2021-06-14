// пример с "бегущей радугой" для библиотеки FastLED
#define NUM_LEDS 206
#include "FastLED.h"
#define PIN 2
CRGB leds[NUM_LEDS];

float Amplitude = 40, Brightness = 255, Centre = NUM_LEDS / 2, treshold = 0.2;
float Hue = 0, Saturation = 0;
String mode = "music"; //"general", "colourPicking", "music"

int micPin = A3; //A5
int topPin = A2; //A2
int midPin = A1; //A1
int botPin = A0; //A0
int switchPins[2] = {8, 7};
boolean lastSwitchValue[2] = {false, false};

long lastTimeDanced = 0;

int micDataLength = 5;
Queue /* biggerMicData(10), */ micData(micDataLength), amplitudes(15);
float maxVolume = 1, minVolume = 0, noiseTreshold = 320;

void setup() {
  Serial.begin(9600);
  FastLED.addLeds<WS2811, PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(255);

  pinMode(switchPins[0], INPUT_PULLUP);
  pinMode(switchPins[1], INPUT_PULLUP);

  micData.Fill(analogRead(micPin));
  amplitudes.Fill(analogRead(micPin));
  //biggerMicData.Fill(analogRead(A5));
}

void loop() {
  //mode calculations
  boolean switchRead0 = !digitalRead(switchPins[0]);
  if (switchRead0 && !lastSwitchValue[0]) {
    delay(10);
    switchRead0 = !digitalRead(switchPins[0]);
    if (switchRead0 && !lastSwitchValue[0]) mode = "general";
  }
  boolean switchRead1 = !digitalRead(switchPins[1]);
  if (switchRead1 && !lastSwitchValue[1]) {
    delay(10);
    switchRead1 = !digitalRead(switchPins[1]);
    if (switchRead1 && !lastSwitchValue[1]) {
      mode = "music";
    }
  }
  if ((!switchRead1 && lastSwitchValue[1]) || (!switchRead0 && lastSwitchValue[0])) {
    if (millis() - lastTimeDanced > 2000) {
      mode = "colourPicking";
      lastTimeDanced = millis();
    }
    else lastTimeDanced = millis();
  }


  //values calculations (specific to modes)
  int a = 10;
  if (mode == "general") {
    Centre = float(int(map(int(1023-analogRead(botPin)) / a * a, 0, 1023, 0, NUM_LEDS - 1)));
    Amplitude = float(int(map(int(1023-analogRead(midPin)) / a * a, 0, 1023, 1, float(NUM_LEDS)*1.1)));
    Brightness = float(int(map(int(1023-analogRead(topPin)) / a * a, 0, 1023, 0, 255)));
  }
  else if (mode == "colourPicking") {
    Hue = float(int(map(int(1023-analogRead(botPin)) / a * a, 0, 1023, 0, 255)));
    Saturation = float(int(map(int(1023-analogRead(midPin)) / a * a, 0, 1023, 0, 255)));
    Brightness = float(int(map(int(1023-analogRead(topPin)) / a * a, 0, 1023, 0, 255)));
    /*
      float r = float(int(map(analogRead(A2), 0, 1023, 0, 255)));
      float g = float(int(map(analogRead(A1), 0, 1023, 0, 255)));
      float b = float(int(map(analogRead(A0), 0, 1023, 0, 255)));
      float rd = r/255.0, gd = g/255.0, bd = b/255.0;
      float Cmax = max(rd, max(gd, bd));
      float Cmin = min(rd, min(gd, bd));
      float delta = Cmax - Cmin;

      if(delta == 0) Hue = 0;
      else if (Cmax == rd) Hue = int(float(int((gd - bd)/delta)%6)*255.0/6.0);
      else if (Cmax == gd) Hue = int(((bd - rd)/delta+2)*255.0/6.0);
      else if (Cmax == bd) Hue = int(((rd - gd)/delta+4)*255.0/6.0);

      if(Cmax == 0) Saturation = 0;
      else Saturation = int(delta/Cmax*255);
    */
  }
  else {
    Brightness = float(int(map(int(1023-analogRead(topPin)) / a * a, 0, 1023, 0, 255)));
    float HueSpeed = float(map(1023-analogRead(midPin), 0, 1023, 0, 140))/100.0;
    
    //if (biggerMicData.Full()) biggerMicData.deQueue();
    //biggerMicData.enQueue(analogRead(A5));
    
    if (micData.Full()) micData.deQueue();
    micData.enQueue(analogRead(micPin));

    Queue bigMicData(micDataLength);
    float micAv = micData.average();
    float count = 0, sum;
    for (int i = 0; i < micDataLength; i++) {
      if (micData.myQueue[i] >= 3 / 2 * micAv && micData.myQueue[i] != micData.emptyValue) {
        count++;
        sum += micData.myQueue[i];
      }
    }
    if (count > 0) {
      if (amplitudes.Full()) amplitudes.deQueue();
      amplitudes.enQueue(sum / count);
    }

    float volume = map(1023-analogRead(botPin), 1023, 0, noiseTreshold*1.2, 1023);
    int Height = constrain(int(map(amplitudes.average(), noiseTreshold, volume, 0, NUM_LEDS / 2)), 0, NUM_LEDS);
    //if (!amplitudes.Empty()) Serial.println(amplitudes.average());
    for (int i = 0; i < NUM_LEDS; i++) {         // от 0 до первой трети
      if (!(i > NUM_LEDS / 2 + Height || i < NUM_LEDS / 2 - Height)) leds[i] = CHSV(int(Hue), 255, Brightness);
      else leds[i] = CHSV(0, 0, 0);
    }
    Hue += HueSpeed;
    if (Hue > 255) Hue = 0;
  }

  if(mode != "music") {
    for (int i = 0; i < NUM_LEDS; i++ ) {         // от 0 до первой трети
      leds[i] = CHSV(Hue, Saturation, theValueFunction(i));
    }
  }
  
  FastLED.show();

  lastSwitchValue[0] = switchRead0;
  lastSwitchValue[1] = switchRead1;
  delay(5);
}

int theValueFunction(float x) {
  x -= Centre;
  float y = Brightness / (pow(2 * x / Amplitude, 2 * Amplitude) + 1);
  if (y < treshold * Brightness) y = 0;
  return int(y);
}
