#include <Servo.h>
#include <Wire.h>
#include <MPU6050.h>
MPU6050 mpu;

#include <SPI.h>
#include "Mirf.h"
#include "nRF24L01.h"
#include "MirfHardwareSpiDriver.h"
Nrf24l Mirf = Nrf24l(9, 10);

byte recieved[20];
byte tosend[2];

Queue pitches(2), rolls(2);

Servo motor, verticalServo, horizontalServo;
