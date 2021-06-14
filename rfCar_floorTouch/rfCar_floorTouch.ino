#include <SPI.h>
#include "Mirf.h"
#include "nRF24L01.h"
#include "MirfHardwareSpiDriver.h"
Nrf24l Mirf = Nrf24l(10, 9);

byte info[15];

int pins[2][2] = {{3, 2}, {6, 5}};

void setup() {
  Serial.begin(115200);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();

  Mirf.setRADDR((byte *)"LOLOL"); //Set your own address (receiver address) using 5 characters
  Mirf.payload = sizeof(info);
  Mirf.channel = 90;             //Set the used channel
  Mirf.config();
  
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      pinMode(pins[i][j], OUTPUT);
    }
  }
  
}

void loop() {
  if (Mirf.dataReady()) { //When the program is received, the received data is output from the serial port
    Mirf.getData((byte *) &info);
  }
  int spid = map(constrain(info[2], 0, 180), 0, 180, -255, 255);
  int turnL = map(constrain(info[1], 0, 180), 0, 180, 255, -255);
  Serial.print(spid);
  Serial.print(" ");
  Serial.println(turnL);
  int rightTotal = spid - turnL;
  int leftTotal = spid + turnL;
  digitalWrite(pins[0][1], rightTotal < 0);
  digitalWrite(pins[1][1], leftTotal < 0);
  if (rightTotal < 0) rightTotal += 255;
  if (leftTotal < 0) leftTotal += 255;
  analogWrite(pins[0][0], rightTotal);
  analogWrite(pins[1][0], leftTotal);
/*
  digitalWrite(pins[0][1],  LOW);
  digitalWrite(pins[1][1],  LOW);
  digitalWrite(pins[0][0],  LOW);
  digitalWrite(pins[1][0],  LOW);
  */

}
