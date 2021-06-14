boolean controllerConnected = false;
long lastDataRecievedTime = 0;

float potRX, potRY, potLY, potLX, potR, potL, button, joystickButton, pultRoll, pultPitch, thisRoll, thisPitch;
void loop() {
  //rf loop
  if (Mirf.dataReady()) { //When the program is received, the received data is output from the serial port
    Mirf.getData((byte *) &recieved);
    controllerConnected = true;
    lastDataRecievedTime = millis();
    //Serial.println("data!");
  }
  if (millis() - lastDataRecievedTime > 500) {
    controllerConnected = false;
  }
  if (controllerConnected) {
    digitalWrite(6, HIGH);
    //main code
    updateAllVariables();
    printAllVariables();
    
    //writing motors
    float motorValue = constrain(map(potLY, 0, 1023, 800, 2300), 800, 2300);
    float verticalValue = constrain(map(potRY, 0, 1023, 0, 180), 0, 180);
    float horizontalValue = constrain(map(potRX, 0, 1023, 0, 180), 0, 180);
    motor.write(motorValue);
    verticalServo.write(verticalValue);
    horizontalServo.write(horizontalValue);

    //to send info
    tosend[0] = int(thisRoll) + 90;
    tosend[1] = int(thisPitch) + 90;

    //sending
    Mirf.setTADDR((byte *)"TPULT");           //Set the receiver address
    Mirf.send((byte *)&tosend);                //Send instructions, send random number value
    Serial.print("Wait for sending.....  ");
    while (Mirf.isSending()) delay(1);        //Until you send successfully, exit the loop
  }
  else {

    digitalWrite(6, LOW);
    //to send info
    
    tosend[0] = int(thisRoll) + 90;
    tosend[1] = int(thisPitch) + 90;

    //sending
    Mirf.setTADDR((byte *)"TPULT");           //Set the receiver address
    Mirf.send((byte *)&tosend);                //Send instructions, send random number value
    Serial.println("Wait for sending.....  ");
    while (Mirf.isSending()) delay(1);        //Until you send successfully, exit the loop

  
    motor.write(0);
    verticalServo.write(95);
    horizontalServo.write(90);
  }
}
