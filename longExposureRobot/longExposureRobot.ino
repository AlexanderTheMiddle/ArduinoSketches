#include <Servo.h>

Servo shoulder;
Servo elbow;

int ledPin = 3;
void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  shoulder.attach(4);
  elbow.attach(5);

  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
}

boolean lineFinished = false;
String line = "";

void loop() {
  /*
  shoulder.write(110);
  delay(2000);
  shoulder.write(80);
  delay(2000);
  */
  
  while (Serial.available()) {
    char inChar = Serial.read();
    if (inChar == '\n') {
      String s = "";
      s += line.charAt(0);
      s += line.charAt(1);
      s += line.charAt(2);
      String e = "";
      e += line.charAt(3);
      e += line.charAt(4);
      e += line.charAt(5);
      char ledData = line.charAt(6);
      
      Serial.println(stringToInt(line));
      shoulder.write(stringToInt(s));
      elbow.write(stringToInt(e));
      if(ledData == '0') digitalWrite(ledPin, LOW);
      else digitalWrite(ledPin, HIGH);
      line = "";
    }
    else line += inChar;
  }
  lineFinished = false;

}

int stringToInt(String line) {
  int number = 0;
  for (int i = line.length() - 1; i > -1; i--) {
    if (int(line.charAt(i)) - int('0') > -1 && int(line.charAt(i)) - int('0') < 10) number += (int(line.charAt(i)) - int('0')) * pow(10, line.length() - 1 - i);
    else {
      Serial.println("string is of incorrect format");
      return 1;
    }
  }
  return number;
}
