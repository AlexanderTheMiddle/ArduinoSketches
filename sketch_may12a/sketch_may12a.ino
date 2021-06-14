String message;

void setup() {
  Serial.begin(9600);

}

void loop() {
  while (Serial.available() > 0) {
    char incomingChar = Serial.read();
    if (incomingChar >= '0' && incomingChar <= '9') {
      message += incomingChar;
    } 
    else if (incomingChar == '0') {
      Serial.println("m");
      message = "";
    }
  }
}
