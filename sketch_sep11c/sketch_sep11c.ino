void setup() {
  Serial.begin(9600);

  pinMode(8, OUTPUT);
  digitalWrite(8, 1);
}
int a;

void loop() {
  //while(Serial.available()) {
Serial.println(analogRead(A1));
a = Serial.read();
  if (a == 49) {
    Serial.println("Согнул руку");
    digitalWrite(8, 0);
    delay(50);
    digitalWrite(8, 1);
    delay(1000);
  }
  delay(1);
  //z == 0;
 // }
}
