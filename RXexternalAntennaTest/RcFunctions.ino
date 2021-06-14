void printAllRecieved() {
  for (int i = 0; i < 6; i++) {
    Serial.print(recieved[i * 2] * 255 + recieved[i * 2 + 1]);
    Serial.print(" ");
  }
  for (int i = 12; i < 16; i++) {
    Serial.print(recieved[i]);
    Serial.print(" ");
  }
  Serial.print(recieved[16]*(1-recieved[17]*2));
  Serial.print(" ");
  Serial.print(recieved[18]*(1-recieved[19]*2));
  Serial.println(" ");
}

void printAllVariables() {
  Serial.print(int(potRX));
  Serial.print(" ");
  Serial.print(int(potRY));
  Serial.print(" ");
  Serial.print(int(potLY));
  Serial.print(" ");
  Serial.print(int(potLX));
  Serial.print(" ");
  Serial.print(int(potR));
  Serial.print(" ");
  Serial.print(int(potL));
  Serial.print(" ");
  Serial.print(int(button));
  Serial.print(" ");
  Serial.print(int(joystickButton));
  Serial.print(" ");
  Serial.print(int(pultRoll));
  Serial.print(" ");
  Serial.print(int(pultPitch));
  Serial.print(" ");
  Serial.print(int(thisRoll));
  Serial.print(" ");
  Serial.print(int(thisPitch));
  Serial.print(" ");
  Serial.println(" ");
}
void updateAllVariables() {
  potRX = 1023 - (recieved[0] * 255 + recieved[1]);
    potRY = 1023 - (recieved[2] * 255 + recieved[3]);
    potLY = recieved[4] * 255 + recieved[5];
    potLX = recieved[6] * 255 + recieved[7];

    potR = recieved[8] * 255 + recieved[9];
    potL = recieved[10] * 255 + recieved[11];

    button = recieved[12];
    joystickButton = recieved[13];

    pultRoll = recieved[16] * (1 - recieved[17] * 2);
    pultPitch = recieved[18] * (1 - recieved[19] * 2);

    // Read normalized values
    //Vector normAccel = mpu.readNormalizeAccel();

    // Calculate Pitch & Roll
    int roll = 90;
    int pitch = 15;
    
    //roll and pitch push
    if (rolls.Full()) rolls.deQueue();
    rolls.enQueue(roll);
    if (pitches.Full()) pitches.deQueue();
    pitches.enQueue(pitch);

    thisRoll = rolls.average();
    thisPitch = pitches.average();
}
