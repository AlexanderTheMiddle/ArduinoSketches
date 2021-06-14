#include <SPI.h>
#include "Mirf.h"
#include "nRF24L01.h"
#include "MirfHardwareSpiDriver.h"
Nrf24l Mirf = Nrf24l(9, 10);

byte recieved[3];
byte tosend[1];

void setup() {
  Serial.begin(9600);

  //radio stuff
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  //Set your own address (receiver address) using 5 characters
  Mirf.setRADDR((byte *)"RTHPP");
  Mirf.payload = sizeof(recieved);
  Mirf.channel = 90;             //Set the used channel
  Mirf.config();
  Serial.println("Listening...");  //Start listening to received data

}

boolean controllerConnected = false;
long lastDataRecievedTime = 0;

void loop() {
  //rf loop
  if (Mirf.dataReady()) { //When the program is received, the received data is output from the serial port
    Mirf.getData((byte *) &recieved);
    controllerConnected = true;
    lastDataRecievedTime = millis();
  }
  if (millis() - lastDataRecievedTime > 500) {
    controllerConnected = false;
  }
  if (true || controllerConnected) {
    Serial.println(recieved[0]);
  }
  
    //sending
    Mirf.setTADDR((byte *)"TTHPC");           //Set the receiver address
    Mirf.send((byte *)&tosend);                //Send instructions, send random number value
    Serial.print("Wait for sending.....  ");
    while (Mirf.isSending()) delay(1);        //Until you send successfully, exit the loop
    delay(10);
}
