//Transmitter program

#include <SPI.h>
#include "Mirf.h"
#include "nRF24L01.h"
#include "MirfHardwareSpiDriver.h"
Nrf24l Mirf = Nrf24l(9, 10);

byte info[6];

int pins[4] = {A2, A3, 3, 8};

void setup() {
  Serial.begin(9600);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  //Set your own address (sender address) using 5 characters
  Mirf.setRADDR((byte *)"QWERT");
  Mirf.payload = sizeof(info);
  Mirf.channel = 90;              //Set the channel used
  Mirf.config();
  
  for(int i = 2; i < 4; i++) {
    pinMode(pins[i], INPUT_PULLUP);
  }
}

void loop() {
  float potX = analogRead(pins[0]);
  float potY = analogRead(pins[1]);
  /*
  for(int i = 7; i < 11; i++) {
    Serial.print(pins[i] - 18);
    Serial.print(": ");
    Serial.print(analogRead(pins[i]));
    Serial.print("   ");
  }
  Serial.println(" ");
  delay(10);
*/

  info[0] = potX / 255;
  info[1] = potX - info[0] * 255;
  info[2] = potY / 255;
  info[3] = potY - info[2] * 255;
  info[4] = !digitalRead(pins[2]);
  info[5] = !digitalRead(pins[3]);


  for(int i = 0; i < 6; i++) {
    Serial.print(info[i]);
    Serial.print("   ");
  }
  Serial.println(" ");
  
  Mirf.setTADDR((byte *)"LOLOL");           //Set the receiver address
  Mirf.send((byte *)&info);                //Send instructions, send random number value
  Serial.print("Wait for sending.....  ");
  while (Mirf.isSending()) delay(1);        //Until you send successfully, exit the loop
  
}

//3 - joystick button
//4 - button
//A3 - up1023 down0
//A2 - right1023 left0
