
#define infopin A3

void setup() {
 Serial.begin(9600);

}

void loop() {
  Serial.println(analogRead(A3));
  delay(3);
}
