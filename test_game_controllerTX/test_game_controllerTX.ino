//Transmitter program

#include <SPI.h>
#include "Mirf.h"
#include "nRF24L01.h"
#include "MirfHardwareSpiDriver.h"
Nrf24l Mirf = Nrf24l(10, 9);

byte info[5];

void setup() {
  Serial.begin(9600);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  //Set your own address (sender address) using 5 characters
  Mirf.setRADDR((byte *)"QWERT");
  Mirf.payload = sizeof(info);
  Mirf.channel = 90;              //Set the channel used
  Mirf.config();

  pinMode(4, INPUT_PULLUP);
}


void loop() {
  int a = !digitalRead(4);
  
  info[0] = a;
  info[1] = a;
  info[2] = a;
  info[3] = a;
  info[4] = a;
  
  Mirf.setTADDR((byte *)"LOLOL");           //Set the receiver address
  Mirf.send((byte *)&info);                //Send instructions, send random number value
  Serial.print("Wait for sending.....  ");
  while (Mirf.isSending()) delay(1);        //Until you send successfully, exit the loop
  Serial.println(a);

}
