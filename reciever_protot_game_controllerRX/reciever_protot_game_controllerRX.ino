
//Receiver program
#include <SPI.h>
#include "Mirf.h"
#include "nRF24L01.h"
#include "MirfHardwareSpiDriver.h"
Nrf24l Mirf = Nrf24l(10, 9);

byte info[15];

void setup()
{
  Serial.begin(115200);
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();

  Mirf.setRADDR((byte *)"LOLOL"); //Set your own address (receiver address) using 5 characters
  Mirf.payload = sizeof(info);
  Mirf.channel = 90;             //Set the used channel
  Mirf.config();
 // Serial.println("Listening...");  //Start listening to received data

}


void loop() {
  //rf loop

  if (Mirf.dataReady()) { //When the program is received, the received data is output from the serial port
    Mirf.getData((byte *) &info);
  }

  for(int i = 0; i<15; i++) {
    Serial.print(info[i]);
    Serial.print(",");
  }
  Serial.println();
  delay(10);
  
}
