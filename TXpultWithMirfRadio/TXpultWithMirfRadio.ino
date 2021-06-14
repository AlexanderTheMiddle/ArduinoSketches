/* Copyright (C) 2012 Kristian Lauszus, TKJ Electronics. All rights reserved.
  This software may be distributed and modified under the terms of the GNU
  General Public License version 2 (GPL2) as published by the Free Software
  Foundation and appearing in the file GPL2.TXT included in the packaging of
  this file. Please note that GPL2 Section 2[b] requires that all works based
  on this software must also be made publicly available under the terms of
  the GPL2 ("Copyleft").
  Contact information
  -------------------
  Kristian Lauszus, TKJ Electronics
  Web      :  http://www.tkjelectronics.com
  e-mail   :  kristianl@tkjelectronics.com
*/
#include <Wire.h>
#include "Mirf.h"
#include "MirfHardwareSpiDriver.h" // Source: https://github.com/TKJElectronics/KalmanFilter
#include <Kalman.h> // Source: https://github.com/TKJElectronics/KalmanFilter
#include <SPI.h>          // библиотека для работы с шиной SPI
#include "nRF24L01.h"     // библиотека радиомодуля
#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library for ST7735
#include <Adafruit_ST7789.h> // Hardware-specific library for ST7789

#define TFT_CS   2
#define TFT_RST  4
#define TFT_DC   3
#define TFT_MOSI 6  // Data out
#define TFT_SCLK 7  // Clock out
//#define TFT_BLK  5 //back lighting

// For ST7735-based displays, we will use this call
Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_MOSI, TFT_SCLK, TFT_RST);

Nrf24l Mirf = Nrf24l(9, 10);
byte tosend[20];
byte recieved[2];
float planeRoll = 90, planePitch = 90;

#define RESTRICT_PITCH // Comment out to restrict roll to ±90deg instead - please read: http://www.freescale.com/files/sensors/doc/app_note/AN3461.pdf
Kalman kalmanX; // Create the Kalman instances
Kalman kalmanY;
/* IMU Data */
double accX, accY, accZ;
double gyroX, gyroY, gyroZ;
int16_t tempRaw;
double gyroXangle, gyroYangle; // Angle calculate using the gyro only
double compAngleX, compAngleY; // Calculated angle using a complementary filter
double kalAngleX, kalAngleY; // Calculated angle using a Kalman filter
uint32_t timer;
uint8_t i2cData[14]; // Buffer for I2C data
// TODO: Make calibration routine
void setup() {
  Serial.begin(115200);
  Serial.println("\nSender address is TPULT \nReciever address is RPULT");
  delay(500);
  
  pinMode(8, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);

  //display stuff
  tft.initR(INITR_MINI160x80);  // Init ST7735S mini display
  tft.setRotation(3);
  tft.fillScreen(ST77XX_WHITE);
  
  //radio stuff
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  //Set your own address (sender address) using 5 characters
  Mirf.setRADDR((byte *)"TPULT");
  Mirf.payload = sizeof(tosend);
  Mirf.channel = 90;              //Set the channel used
  Mirf.config();



  Wire.begin();
#if ARDUINO >= 157
  Wire.setClock(400000UL); // Set I2C frequency to 400kHz
#else
  TWBR = ((F_CPU / 400000UL) - 16) / 2; // Set I2C frequency to 400kHz
#endif
  i2cData[0] = 7; // Set the sample rate to 1000Hz - 8kHz/(7+1) = 1000Hz
  i2cData[1] = 0x00; // Disable FSYNC and set 260 Hz Acc filtering, 256 Hz Gyro filtering, 8 KHz sampling
  i2cData[2] = 0x00; // Set Gyro Full Scale Range to ±250deg/s
  i2cData[3] = 0x00; // Set Accelerometer Full Scale Range to ±2g
  while (i2cWrite(0x19, i2cData, 4, false)); // Write to all four registers at once
  while (i2cWrite(0x6B, 0x01, true)); // PLL with X axis gyroscope reference and disable sleep mode
  while (i2cRead(0x75, i2cData, 1));
  if (i2cData[0] != 0x68) { // Read "WHO_AM_I" register
    Serial.print(F("Error reading sensor"));
    while (1);
  }
  delay(100); // Wait for sensor to stabilize
  /* Set kalman and gyro starting angle */
  while (i2cRead(0x3B, i2cData, 6));
  accX = (int16_t)((i2cData[0] << 8) | i2cData[1]);
  accY = (int16_t)((i2cData[2] << 8) | i2cData[3]);
  accZ = (int16_t)((i2cData[4] << 8) | i2cData[5]);
  // Source: http://www.freescale.com/files/sensors/doc/app_note/AN3461.pdf eq. 25 and eq. 26
  // atan2 outputs the value of -π to π (radians) - see http://en.wikipedia.org/wiki/Atan2
  // It is then converted from radians to degrees
#ifdef RESTRICT_PITCH // Eq. 25 and 26
  double roll  = atan2(accY, accZ) * RAD_TO_DEG;
  double pitch = atan(-accX / sqrt(accY * accY + accZ * accZ)) * RAD_TO_DEG;
#else // Eq. 28 and 29
  double roll  = atan(accY / sqrt(accX * accX + accZ * accZ)) * RAD_TO_DEG;
  double pitch = atan2(-accX, accZ) * RAD_TO_DEG;
#endif
  kalmanX.setAngle(roll); // Set starting angle
  kalmanY.setAngle(pitch);
  gyroXangle = roll;
  gyroYangle = pitch;
  compAngleX = roll;
  compAngleY = pitch;
  timer = micros();
}


int pots[6] = {A2, A3, A0, A1, A6, A7};
int re;
float ROLL, r, h, xr, yr, xl, yl, xt, yt, xc, yc;
float sensitivityBar = 1;
long lastTimeUpdatedDisplay = 0;
long displayRefreshPeriod = 400;
boolean receiverConnected = false;
long lastDataRecievedTime = 0;

void loop() {
  /* Update all the values */
  while (i2cRead(0x3B, i2cData, 14));
  accX = (int16_t)((i2cData[0] << 8) | i2cData[1]);
  accY = (int16_t)((i2cData[2] << 8) | i2cData[3]);
  accZ = (int16_t)((i2cData[4] << 8) | i2cData[5]);
  tempRaw = (int16_t)((i2cData[6] << 8) | i2cData[7]);
  gyroX = (int16_t)((i2cData[8] << 8) | i2cData[9]);
  gyroY = (int16_t)((i2cData[10] << 8) | i2cData[11]);
  gyroZ = (int16_t)((i2cData[12] << 8) | i2cData[13]);;
  double dt = (double)(micros() - timer) / 1000000; // Calculate delta time
  timer = micros();
  // Source: http://www.freescale.com/files/sensors/doc/app_note/AN3461.pdf eq. 25 and eq. 26
  // atan2 outputs the value of -π to π (radians) - see http://en.wikipedia.org/wiki/Atan2
  // It is then converted from radians to degrees
#ifdef RESTRICT_PITCH // Eq. 25 and 26
  double roll  = atan2(accY, accZ) * RAD_TO_DEG;
  double pitch = atan(-accX / sqrt(accY * accY + accZ * accZ)) * RAD_TO_DEG;
#else // Eq. 28 and 29
  double roll  = atan(accY / sqrt(accX * accX + accZ * accZ)) * RAD_TO_DEG;
  double pitch = atan2(-accX, accZ) * RAD_TO_DEG;
#endif
  double gyroXrate = gyroX / 131.0; // Convert to deg/s
  double gyroYrate = gyroY / 131.0; // Convert to deg/s
#ifdef RESTRICT_PITCH
  // This fixes the transition problem when the accelerometer angle jumps between -180 and 180 degrees
  if ((roll < -90 && kalAngleX > 90) || (roll > 90 && kalAngleX < -90)) {
    kalmanX.setAngle(roll);
    compAngleX = roll;
    kalAngleX = roll;
    gyroXangle = roll;
  } else
    kalAngleX = kalmanX.getAngle(roll, gyroXrate, dt); // Calculate the angle using a Kalman filter
  if (abs(kalAngleX) > 90)
    gyroYrate = -gyroYrate; // Invert rate, so it fits the restriced accelerometer reading
  kalAngleY = kalmanY.getAngle(pitch, gyroYrate, dt);
#else
  // This fixes the transition problem when the accelerometer angle jumps between -180 and 180 degrees
  if ((pitch < -90 && kalAngleY > 90) || (pitch > 90 && kalAngleY < -90)) {
    kalmanY.setAngle(pitch);
    compAngleY = pitch;
    kalAngleY = pitch;
    gyroYangle = pitch;
  } else
    kalAngleY = kalmanY.getAngle(pitch, gyroYrate, dt); // Calculate the angle using a Kalman filter
  if (abs(kalAngleY) > 90)
    gyroXrate = -gyroXrate; // Invert rate, so it fits the restriced accelerometer reading
  kalAngleX = kalmanX.getAngle(roll, gyroXrate, dt); // Calculate the angle using a Kalman filter
#endif
  gyroXangle += gyroXrate * dt; // Calculate gyro angle without any filter
  gyroYangle += gyroYrate * dt;
  //gyroXangle += kalmanX.getRate() * dt; // Calculate gyro angle using the unbiased rate
  //gyroYangle += kalmanY.getRate() * dt;
  compAngleX = 0.93 * (compAngleX + gyroXrate * dt) + 0.07 * roll; // Calculate the angle using a Complimentary filter
  compAngleY = 0.93 * (compAngleY + gyroYrate * dt) + 0.07 * pitch;
  // Reset the gyro angle when it has drifted too much
  if (gyroXangle < -180 || gyroXangle > 180)
    gyroXangle = kalAngleX;
  if (gyroYangle < -180 || gyroYangle > 180)
    gyroYangle = kalAngleY;
  /* Print Data */
#if 1 // Set to 1 to activate
  /*
    Serial.print(accX ); Serial.print("\t");
    Serial.print(accY ); Serial.print("\t");
    Serial.print(accZ ); Serial.print("\t");
    Serial.print(gyroX); Serial.print("\t");
    Serial.print(gyroY); Serial.print("\t");
    Serial.print(gyroZ); Serial.print("\t");
    Serial.print("\t");
  */
  /*
    Serial.print("Gyr_X: "); Serial.print(int(roll)); Serial.print("\t");
    Serial.print("    )))))) "); Serial.print(int(gyroXangle)); Serial.print("\t");
    Serial.print("TTTTTT "); Serial.print(int(compAngleX)); Serial.print("\t");
    Serial.print("    St_d_X: "); Serial.print(int(kalAngleX)); Serial.print("\t");
    Serial.print("\t");
    Serial.print("------- "); Serial.print(int(pitch)); Serial.print("\t");
    Serial.print("    Gd_Y: "); Serial.print(int(gyroYangle)); Serial.print("\t");
    Serial.print("    Guro_aace: "); Serial.print(int(compAngleY)); Serial.print("\t");
    Serial.print("    ToToToTo "); Serial.print(int(kalAngleY)); Serial.print("\t");
  */

#endif
  /*
    Serial.print(accX ); Serial.print("\t");
    Serial.print(accY ); Serial.print("\t");
    Serial.print(accZ ); Serial.print("\t");
    Serial.print(gyroX); Serial.print("\t");
    Serial.print(gyroY); Serial.print("\t");
    Serial.print(gyroZ); Serial.print("\t");
    Serial.print("\t");

    Serial.print("Gyr_X: "); Serial.print(int(roll)); Serial.print("\t");
    Serial.print("    )))) "); Serial.print(int(gyroXangle)); Serial.print("\t");
    Serial.print("TTT "); Serial.print(int(compAngleX)); Serial.print("\t");
    Serial.print("    St_d_X: "); Serial.print(int(kalAngleX)); Serial.print("\t");
    Serial.print("\t");
    Serial.print("---- "); Serial.print(int(pitch)); Serial.print("\t");
    Serial.print("    Gd_Y: "); Serial.print(int(gyroYangle)); Serial.print("\t");
    Serial.print("    Guro_aace: "); Serial.print(int(compAngleY)); Serial.print("\t");
    Serial.print("    ToToToTo "); Serial.print(int(kalAngleY)); Serial.print("\t");
  */
  
  //recieving
  if (Mirf.dataReady()) { //When the program is received, the received data is output from the serial port
    Mirf.getData((byte *) &recieved);
    if(!receiverConnected) tft.fillScreen(ST77XX_WHITE);
    receiverConnected = true;
    lastDataRecievedTime = millis();
  }
  if (millis() - lastDataRecievedTime > 500) {
    receiverConnected = false;
  }
  
  planeRoll = recieved[0] - 90;
  planePitch = recieved[1] - 90;
  
  //основной код
  if(millis() - lastTimeUpdatedDisplay > displayRefreshPeriod) {
    if(receiverConnected) {
    lastTimeUpdatedDisplay = millis();
    
    tft.drawTriangle(xr, yr, xl, yl, xt, yt, ST77XX_WHITE);
    tft.fillRect( tft.width()*0.9, sensitivityBar + tft.height()*0.2, 5, tft.height()*0.8 - sensitivityBar, ST77XX_WHITE);
  
  
    ROLL = (planeRoll)/180.0*PI;
    r = tft.height()/2.0;
    h = r/3.0;
    xc = tft.width()/2.0;
    yc = tft.height()/2.0;
    
    xr = r*cos(ROLL) + xc;
    yr = r*sin(ROLL) + yc;
    xl = -r*cos(ROLL) + xc;
    yl = -r*sin(ROLL) + yc;
    xt = -h*cos(90+ROLL) + xc - tft.width()/40.0;
    yt = -h*sin(90+ROLL) + yc;
    
    tft.drawTriangle(xr, yr, xl, yl, xt, yt, ST77XX_GREEN);
    
    sensitivityBar = map(analogRead(A7), 1023, 0, 0, tft.height()*0.7);

    tft.fillRect( tft.width()*0.9, sensitivityBar + tft.height()*0.2, 5, tft.height()*0.8 - sensitivityBar, ST77XX_MAGENTA);
    }
    else {
      tft.fillScreen(ST77XX_YELLOW);
      tft.setCursor(tft.width()*0.43, tft.height()*0.28);
      tft.setTextSize(6);
      tft.setTextColor(ST77XX_WHITE);
      tft.setTextWrap(true);
      tft.print("!");
    }
  }
  /*
  float cx = 1023 - analogRead(pots[0]);
  float cy = analogRead(pots[1]);
  tft.fillCircle(cx/1023.0*tft.width(), cy/1023.0*tft.height(), tft.height()/10.0, ST77XX_GREEN);
  delay(200);
  tft.fillCircle(cx/1023.0*tft.width(), cy/1023.0*tft.height(), tft.height()/10.0, ST77XX_WHITE);
  */
  
  //joysticks and pots
  for (int i = 0; i < 6; i++) {
    re = analogRead(pots[i]);
    tosend[i * 2] = re / 255;
    tosend[i * 2 + 1] = re - tosend[i * 2] * 255;
  }

  //buttons
  tosend[12] = digitalRead(8);
  tosend[13] = digitalRead(5);

  //angles
  tosend[16] = abs(int(compAngleX));
  tosend[17] = (compAngleX < 0);
  tosend[18] = abs(int(compAngleY));
  tosend[19] = (compAngleY < 0);
  
  for (int i = 0; i < 6; i++) {
    Serial.print(tosend[i * 2] * 255 + tosend[i * 2 + 1]);
    Serial.print(" ");
  }
  for (int i = 12; i < 16; i++) {
    Serial.print(tosend[i]);
    Serial.print(" ");
  }
  Serial.print(tosend[16]*(1-tosend[17]*2));
  Serial.print(" ");
  Serial.print(tosend[18]*(1-tosend[19]*2));
  Serial.print(" ");

  Serial.print(planeRoll);
  Serial.print(" ");
  Serial.print(planePitch);
  Serial.println(" ");

  //sending
  Mirf.setTADDR((byte *)"RPULT");           //Set the receiver address
  Mirf.send((byte *)&tosend);                //Send instructions, send random number value
  Serial.print("Wait for sending.....  ");
  while (Mirf.isSending()) delay(1);        //Until you send successfully, exit the loop

#if 0 // Set to 1 to print the temperature
  Serial.print("\t");
  double temperature = (double)tempRaw / 340.0 + 36.53;
  Serial.print(temperature); Serial.print("\t");
#endif
  Serial.print("\r\n");
  delay(2);
}
