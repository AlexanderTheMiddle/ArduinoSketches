#define NUM_LEDS 12
#include "FastLED.h"
#define PIN 9
CRGB leds[NUM_LEDS];

#include <Wire.h>
#include <MPU6050.h>
MPU6050 mpu;

#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_I2CDevice.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, 6);


void setup() {
  Serial.begin(9600);

  FastLED.addLeds<WS2811, PIN, GRB>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(255);
  
  //Initialize MPU6050
  while (!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for (;;); // Don't proceed, loop forever
  }

  display.display();
  delay(500); // Pause for 2 seconds
}

int lastPitch = 0, lastRoll = 0;
void loop() {
  
  for(int i = 0; i < 12; i++) {
    leds[i] = CHSV(0, 0, 0);
  }
  leds[int(millis()/1000)%12] = CHSV(150, 150, 150);

  FastLED.show();

  Vector normAccel = mpu.readNormalizeAccel();
  int pitch = (atan2(normAccel.XAxis, sqrt(normAccel.YAxis * normAccel.YAxis + normAccel.ZAxis * normAccel.ZAxis)) * 180.0) / M_PI;
  int roll = (atan2(normAccel.YAxis, normAccel.ZAxis) * 180.0) / M_PI;
  roll = sgn(roll)*(180 - abs(roll));
  //Serial.print(pitch-lastPitch);
  //Serial.print(" ");
  Serial.println(roll-lastRoll);

  display.clearDisplay();
  display.setTextSize(2); // Draw 2X-scale text
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println("NOT NOT");
  display.setCursor(10, 25);
  display.println("NOT");
  display.setCursor(10, 50);
  display.println("G");
  display.display();

  lastPitch = pitch;
  lastRoll = roll;
  delay(10);
}

float sgn(float a) {
  if(a == 0) return 0;
  else if(a > 0) return 1;
  else return -1;
}
