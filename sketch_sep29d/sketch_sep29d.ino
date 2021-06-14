int pins[5] = {A4, 6, 7, A5, 5};
//order            pins
//  2               6
//1 5 3          A4 5 7
//  4              A5

#define rotorPin A7

#define leftPin pins[0]
#define upPin pins[1]
#define rightPin pins[2]
#define downPin pins[3]
#define okPin pins[4]

void setup() {
  Serial.begin(9600); 
}

void loop() {
  for (int i = 0; i < 8; i++) {
    //if(!digitalRead(i))
    Serial.print(i);
    Serial.print(": ");
    Serial.print(analogRead(i));
    Serial.print("      ");
  }
  Serial.println(" ");
  delay(10);
}


/*

01000001 //
01101100 //
01100101 //
01111000 //
01100001 //
01101110 //
01100100
01100101
01110010


41  6C  65  78  61 6E
*/
