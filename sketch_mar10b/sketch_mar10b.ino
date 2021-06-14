#include <Servo.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_I2CDevice.h>
#include <GyverEncoder.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

Encoder encoder(5, 6, 7);
#define ledPin 8
int potpin = A0;  // analog pin used to connect the potentiometer

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);

  encoder.setType(TYPE1);
  //encoder.setTickMode(AUTO);
  
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.clearDisplay();
}

float f = 95;    // variable to read the value from the analog pin
long LEDt = 0, LEDduration = 400, LEDspacing = int(1000000/f);
boolean LEDstate = false;

void loop() {
  float scaler = 1;
  boolean changed = false;
  encoder.tick();
  if(encoder.isTurn()) changed = true;
  if(encoder.isRight()) f+= 0.1*scaler;
  if(encoder.isLeft()) f -= 0.1*scaler;
  if(encoder.isRightH()) f+= 1*scaler;
  if(encoder.isLeftH()) f -= 1*scaler;
  f = abs(f);
  
  LEDspacing = max(int(1000000/f) - LEDduration, 10);

  if(LEDstate && micros() - LEDt > LEDduration) {
    LEDt = micros();
    LEDstate = !LEDstate;
    digitalWrite(ledPin, LEDstate);
  }
  
  else if(!LEDstate && micros() - LEDt > LEDspacing) {
    LEDt = micros();
    LEDstate = !LEDstate;
    digitalWrite(ledPin, LEDstate);
  }
  
  if(changed) {
    display.clearDisplay();
  display.setTextSize(3);             // Normal 1:1 pixel scale
  display.setTextColor(SSD1306_WHITE);        // Draw white text
  display.setCursor(0,0);             // Start at top-left corner
  display.println(f);
  display.display();
  }

}

//0 - 530
