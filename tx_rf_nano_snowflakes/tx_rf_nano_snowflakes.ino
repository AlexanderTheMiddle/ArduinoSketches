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

  pinMode(A5, INPUT_PULLUP);
  pinMode(3, OUTPUT);
}

int potx, poty, potxo, potyo, buttonNow = 0, buttonWas = 0;
boolean regularMode = true;
void loop()
{
  buttonNow = digitalRead(A5);
  buttonNow =  int(!boolean(buttonNow));

  if (buttonNow == 1 && buttonWas == 0) {
    regularMode = !regularMode;
  }

  if (!regularMode && buttonNow == 1) {
    for (int i = 0; i < 100; i++) {
      potx = analogRead(A1);
      poty = analogRead(A0);
      buttonNow = digitalRead(A5);
      buttonNow =  int(!boolean(buttonNow));
      delay(1);
    }
  }
  else delay(100);

  info[0] = potx / 255;
  info[1] = potx - info[0] * 255;
  info[2] = poty / 255;
  info[3] = poty - info[2] * 255;
  info[4] = buttonNow;
  

  if (regularMode) {
    potxo = 200;
    potyo = 100;
  }
  else if (!regularMode && buttonNow == 1) {
    potxo = info[0] * 255 + info[1];
    potyo = info[2] * 255 + info[3];
  }


  info[0] = potxo / 255;
  info[1] = potxo - info[0] * 255;
  info[2] = potyo / 255;
  info[3] = potyo - info[2] * 255;
  info[4] = buttonNow;



  Mirf.setTADDR((byte *)"LOLOL");           //Set the receiver address
  Mirf.send((byte *)&info);                //Send instructions, send random number value
  Serial.print("Wait for sending.....  ");
  while (Mirf.isSending()) delay(1);        //Until you send successfully, exit the loop
  Serial.print(potxo);
  Serial.print("  ");
  Serial.print(potyo);
  Serial.print("  ");
  Serial.println(regularMode);

  buttonWas = buttonNow;
  analogWrite(3, 10*int(!regularMode));
}
