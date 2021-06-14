#include <SPI.h>
#include "Mirf.h"
#include "nRF24L01.h"
#include "MirfHardwareSpiDriver.h"
Nrf24l Mirf = Nrf24l(9, 10);

byte recieved[1];
byte tosend[3];

int modeButton = 3;
int onOffButton = 4;

int durationPot = A0;
int spacingPot = A1;

int onOffLed = 7;
int durationLed = 5;
int spacingLed = 6;

int connectionLed = 2;
boolean onOfflastState = true;
boolean allowOn = false;

void setup() {
  Serial.begin(9600);

  //radio stuff
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  Mirf.setRADDR((byte *)"TTHPC");
  Mirf.payload = sizeof(tosend);
  Mirf.channel = 90;             //Set the used channel
  Mirf.config();

  
  pinMode(modeButton, INPUT_PULLUP);
  pinMode(onOffButton, INPUT_PULLUP);

  pinMode(durationLed, OUTPUT);
  pinMode(spacingLed, OUTPUT);
  pinMode(onOffLed, OUTPUT);
  pinMode(connectionLed, OUTPUT);
}

boolean controllerConnected = false;
long lastDataRecievedTime = 0;

int minDuration = 0, maxDuration = 3000;
int minSpacing = 0, maxSpacing = 6000;
void loop() {
Serial.println(analogRead(A0));
  /*
  //rf loop
  if (Mirf.dataReady()) { //When the program is received, the received data is output from the serial port
    Mirf.getData((byte *) &recieved);
    controllerConnected = true;
    lastDataRecievedTime = millis();
  }
  if (millis() - lastDataRecievedTime > 500) {
    controllerConnected = false;
  }

  */
  if (true || controllerConnected) {
    //digitalWrite(onOffLed, 0);
    float duration = map(analogRead(durationPot), 1023, 0, minDuration, maxDuration);
    float spacing = map(analogRead(spacingPot), 1023, 0, minSpacing, maxSpacing);
    analogWrite(durationLed, 255 - analogRead(durationPot)/4);
    analogWrite(spacingLed, 255 - analogRead(spacingPot)/4);
    if(!digitalRead(onOffButton) && onOfflastState) allowOn = !allowOn;
    digitalWrite(onOffLed, int(allowOn));
    onOfflastState = digitalRead(onOffButton);

    tosend[0] = byte(allowOn);
    tosend[1] = duration/100;
    tosend[2] = spacing/100;
    //tosend[0] = byte(33);
  }
  
  if(controllerConnected) {
    digitalWrite(connectionLed, LOW);
  }
  else digitalWrite(connectionLed, HIGH);
  
  //tosend[0] = byte(analogRead);
    
  //sending
  Mirf.setTADDR((byte *)"RTHPP");           //Set the receiver address
  Mirf.send((byte *)&tosend);                //Send instructions, send random number value
  Serial.print("Wait for sending.....  ");
  while (Mirf.isSending()) delay(1);        //Until you send successfully, exit the loop
  delay(10);
}
