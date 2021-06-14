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
#include <Kalman.h> // Source: https://github.com/TKJElectronics/KalmanFilter

#define RESTRICT_PITCH // Comment out to restrict roll to ±90deg instead - please read: http://www.freescale.com/files/sensors/doc/app_note/AN3461.pdf

Kalman kalmanX; // Create the Kalman instances
Kalman kalmanY;
int side;

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







//,lchegedfgcgvjhbnkjnjkbhbvvjgvhgvgcvvgcgcgcgcgcgcgcgcgcggcgcgccgcgcgcgcgcgc
/*     #define NUM_LEDS 4
#include "FastLED.h"
#define PIN 14
CRGB leds[NUM_LEDS];
#define SIDELEDS 4       */

#include <FastLED.h>

#define LED_PIN     14
#define NUM_LEDS    4
#define BRIGHTNESS  100
#define LED_TYPE    WS2811
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

//#define UPDATES_PER_SECOND 100





int s;
int c;

int slast = random(442) % 4;
int slast2 = (slast+1) % 4;

int clast = random(144) % 4;
int clast2 = (clast + 1) % 4;

int s_count = 0;
int c_count = 0;

int side_colour_now[4] = {0, 0, 0, 0};

int time_pins[5] = {10, 16, 9, 6, 5};

int colour_pins[4] = {A0, A1, A2, A3};

int co1[4] = {255, 90, 10, 160};
int co2[4] = {235, 255, 255, 200};
int co3[4] = {225, 230, 225, 230};

boolean side_and_col_ok = 0;
boolean NEoff = 1;
boolean startReading = 0;
boolean colours_are_same = 1;
boolean time_is_up = 0;
boolean cameback = 1;

int itime;
int timeb;
long long lasttime;
int raannd;

void setup() {
  Serial.begin(115200);
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





  

  /*FastLED.addLeds<WS2811, PIN, GRB>(side_colour_now, SIDELEDS).setCorrection( TypicalLEDStrip );
  FastLED.setBrightness(100);
  pinMode(13, OUTPUT);

  FastLED.show(); */

delay( 3000 ); // power-up safety delay
    FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
    FastLED.setBrightness(  BRIGHTNESS );


pinMode(A0, OUTPUT);
pinMode(A1, OUTPUT);
pinMode(A2, OUTPUT);
pinMode(A3, OUTPUT);
pinMode(8, OUTPUT);
for(int q = 0; q < 5; q++) {
  pinMode(time_pins[q], OUTPUT);
}

//показываем все цвета
delay(1000);
for(int q = 0; q < 4; q++) {
  for(int w = 0; w < 4; w++) {
    leds[w] = CHSV(co1[q], co2[q], co3[q]);
  }
  FastLED.show();
  digitalWrite(colour_pins[q], HIGH);
  delay(1000);
  digitalWrite(colour_pins[q], LOW);
}
for(int w = 0; w < 4; w++) {
    leds[w] = CHSV(0, 0, 0);
  }
  FastLED.show();
  delay(2000);



  
}

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
#if 0 // Set to 1 to activate
  Serial.print(accX); Serial.print("\t");
  Serial.print(accY); Serial.print("\t");
  Serial.print(accZ); Serial.print("\t");

  Serial.print(gyroX); Serial.print("\t");
  Serial.print(gyroY); Serial.print("\t");
  Serial.print(gyroZ); Serial.print("\t");

  Serial.print("\t");
#endif
raannd = kalAngleX;
if (!startReading) {
  side = -1;
  s = random(764) % 4;
  if (s != slast2) {
    if (s == slast) s_count++;
    if (s != slast || s == slast && s_count % 2 == 0) {
      c = random(234) % 4;
      if (c != clast2) {
        if (c == clast) c_count++;
        if (c != clast || c == clast && c_count % 2 == 0) {
          side_and_col_ok = 1;
          
          side_colour_now[s] = c;
          // ниже я присваиваю сторонам рандомные цвета
          colours_are_same = 1;
          //while(colours_are_same) { kbgfdtyufylggfgihuihdufhdighifgjifgjijgirjirgjgriirgjirjgir
            Serial.println("IN");
            for(int q = 0; q < 4; q++) {
              if(q != s) side_colour_now[q] = random(110) % 4;
              delay(1);
            }
            colours_are_same = 0;
            if(side_colour_now[0] == side_colour_now[1] && side_colour_now[0] == side_colour_now[2] && side_colour_now[0] == side_colour_now[3]) colours_are_same = 1;    
          //}
          Serial.println(!NEoff);
          NEoff = random(922) % 2;
          digitalWrite(8, !NEoff);
          for(int q = 0; q < 4; q++) {
            leds[q] = CHSV(co1[side_colour_now[q]], co2[side_colour_now[q]], co3[side_colour_now[q]]);
          }
          FastLED.show();
          digitalWrite(colour_pins[c], HIGH);
          for(int q = 0; q < 5; q++) {
            digitalWrite(time_pins[q], HIGH);
            itime = 0;
            timeb = 255;
            lasttime = millis();
            startReading = 1;
            time_is_up = 0;
          }
        }
      }   
    }
  }
}// тут заканчивается запись начальных данных и дальше идёт ожидание ответа игрока
if(startReading) {
  if(timeb == 0) {
    itime++;
    timeb = 255;
  }
  if(lasttime + 1  <= millis()) {
    lasttime = millis();
    timeb--;
    analogWrite(time_pins[itime], timeb);
  }
  Serial.println("Time goes");
  if(itime == 4 && timeb == 0) {

for(int j = 0; j < 226; j++) {
          for (int i = 0; i < NUM_LEDS; i++ ) {         // от 0 до первой трети
            leds[i] = CHSV(255, 235, j);  // HSV. Увеличивать HUE (цвет)
            // умножение i уменьшает шаг радуги
          }
          FastLED.show();
          delay(3);
          time_is_up = 1;
          startReading = 0;
          side = -1;
        }
        delay(4000);

    
  }
  //начинаем чекать гироскоп
  if (!time_is_up) {
    if(cameback) {
  if(kalAngleX > 0 && kalAngleX < 145) {
    side = 0;
    Serial.print("SIDE: ");
    Serial.println(side);
    cameback = 0;
    delay(500);
  }
  if(kalAngleX > -145 && kalAngleX < 0) {    
    side = 2;
    Serial.print("SIDE: ");
    Serial.println(side);
    cameback = 0;
    delay(500);
  }
  if(compAngleY > -5) {
    side = 1;
    Serial.println(compAngleY);
    Serial.print("SIDE: ");
    Serial.println(side);
    cameback = 0;
    delay(500);
  }
  if(compAngleY < -85) {
    side = 3;
    Serial.print("SIDE: ");
    Serial.println(side);
    cameback = 0;
    delay(500);
  }
  //while() {
  //  delay(3);
  //}
  //delay(200);
    }
  if( (kalAngleX > 0 && kalAngleX > 150 || kalAngleX < -150 && kalAngleX < 0) && compAngleY < -10 && compAngleY > -70) {
    cameback = 1;
  }
  if (side != -1) {
    digitalWrite(colour_pins[c], LOW);
    startReading = 0;
      if (NEoff && side_colour_now[side] != c || !NEoff && side_colour_now[side] == c)  {
        Serial.println("wrong");
        for(int j = 0; j < 226; j++) {
          for (int i = 0; i < NUM_LEDS; i++ ) {         // от 0 до первой трети
            leds[i] = CHSV(255, 235, j);  // HSV. Увеличивать HUE (цвет)
            // умножение i уменьшает шаг радуги
          }
          FastLED.show();
          delay(3);
          
        }
        side = -1;
        delay(4000);
        startReading = 0;
      }
    
  }
}
}
}









int myrandom() {
  pinMode(A2, INPUT);
  int ran = (analogRead(3) * analogRead(A2)) % 4;
  pinMode(A2, OUTPUT);
  return ran;
}
