#define fase_pin 7
int fase = 0;
void setup() {
  Serial.begin(9600);
  pinMode(fase_pin, INPUT_PULLUP);

}

void loop() {
  if (digitalRead(fase_pin)) Serial.println("0");
  if (!digitalRead(fase_pin)) Serial.println("1");
  delay(3);
}
