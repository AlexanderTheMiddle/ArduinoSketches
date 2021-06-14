boolean controllerConnected = false;
long lastDataRecievedTime = 0;

float potRX, potRY, potLY, potLX, potR, potL, button, joystickButton, pultRoll, pultPitch, thisRoll, thisPitch;
void loop() {
  //rf loop
  if (Mirf.dataReady()) { //When the program is received, the received data is output from the serial port
    Mirf.getData((byte *) &recieved);
    controllerConnected = true;
    lastDataRecievedTime = millis();
  }
  if (millis() - lastDataRecievedTime > 50) {
    controllerConnected = false;
  }
  if (controllerConnected) {
    //main code
    updateAllVariables();
    printAllVariables();

    tosend[0] = int(-thisRoll) + 90;
    tosend[1] = int(thisPitch) + 90;

    //sending
    Mirf.setTADDR((byte *)"TPULT");           //Set the receiver address
    Mirf.send((byte *)&tosend);                //Send instructions, send random number value
    Serial.print("Wait for sending.....  ");
    while (Mirf.isSending()) delay(1);        //Until you send successfully, exit the loop
  }
}
