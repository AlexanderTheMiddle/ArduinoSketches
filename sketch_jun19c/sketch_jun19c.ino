#define led 7

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  
}
boolean was = digitalRead(A0);
int n = 1;
int nl = 0;
void loop() {
  Serial.println(digitalRead(A0));
  delay(1);
}
