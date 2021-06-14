void setup() {
  Serial.begin(9600);
  
  //attaching motors
  verticalServo.attach(7);
  horizontalServo.attach(6);
  motor.attach(8);
  motor.write(2300);
  delay(2000);
  motor.write(800);
  delay(6000);

  //radio stuff
  Mirf.spi = &MirfHardwareSpi;
  Mirf.init();
  //Set your own address (receiver address) using 5 characters
  Mirf.setRADDR((byte *)"RPULT");
  Mirf.payload = sizeof(recieved);
  Mirf.channel = 90;             //Set the used channel
  Mirf.config();
  
  Serial.println("Listening...");  //Start listening to received data

  //Initialize MPU6050
  while(!mpu.begin(MPU6050_SCALE_2000DPS, MPU6050_RANGE_2G))
  {
    Serial.println("Could not find a valid MPU6050 sensor, check wiring!");
    delay(500);
  }

  pitches.Fill(pitches.emptyValue);
  rolls.Fill(rolls.emptyValue);
}
