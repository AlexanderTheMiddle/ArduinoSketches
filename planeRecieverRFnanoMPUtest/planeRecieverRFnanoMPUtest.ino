/*
    MPU6050 Triple Axis Gyroscope & Accelerometer. Pitch & Roll Accelerometer Example.
    Read more: http://www.jarzebski.pl/arduino/czujniki-i-sensory/3-osiowy-zyroskop-i-akcelerometr-mpu6050.html
    GIT: https://github.com/jarzebski/Arduino-MPU6050
    Web: http://www.jarzebski.pl
    (c) 2014 by Korneliusz Jarzebski
*/

#include <Wire.h>
#include <MPU6050.h>
#include <Keyboard.h>
MPU6050 mpu;
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
  //Set your own address (sender address) using 5 characters
  Mirf.setRADDR((byte *)"XPULT");
  Mirf.payload = sizeof(info);
  Mirf.channel = 90;              //Set the channel used
  Mirf.config();
  
  //Initialize MPU6050
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }
}

int serialChecker = 1;
int pitches[20], rolls[20];
void loop()
{
  // Read normalized values 
  Vector normAccel = mpu.readNormalizeAccel();

  // Calculate Pitch & Roll
  int pitch = -(atan2(normAccel.XAxis, sqrt(normAccel.YAxis*normAccel.YAxis + normAccel.ZAxis*normAccel.ZAxis))*180.0)/M_PI;
  int roll = (atan2(normAccel.YAxis, normAccel.ZAxis)*180.0)/M_PI;

  // Output
  pushPitches(pitch);
  pushRolls(roll);
  
  serialChecker = (serialChecker+1)%150;

  info[0] = serialChecker;
  info[1] = int(average(pitches))+90;
  info[2] = int(average(rolls))+90;

  for(int i = 3; i < 15; i++) {
    info[i] = 0;
  }
  
  for(int i = 1; i<15; i++) {
    Serial.print(info[i]);
    Serial.print(",");
  }
  Serial.println();
  
  Mirf.setTADDR((byte *)"RPULT");           //Set the receiver address
  Mirf.send((byte *)&info);                //Send instructions, send random number value
  //Serial.print("Wait for sending.....  ");
  while (Mirf.isSending()) delay(1);        //Until you send successfully, exit the loop
  delay(5);
}

void pushPitches(int valuee) {
  int len = sizeof(pitches);
  for(int i = len-1; i > 0; i--) {
    pitches[i] = pitches[i-1];
  }
  pitches[0] = valuee;
}

void pushRolls(int valuee) {
  int len = sizeof(rolls);
  for(int i = len-1; i > 0; i--) {
    rolls[i] = rolls[i-1];
  }
  rolls[0] = valuee;
}

float average(int a[]) {
  float len = sizeof(a);
  float summ = 0;
  for(int i = 0; i < len; i++) {
    summ+=a[i];
  }
  return summ/len;
}
