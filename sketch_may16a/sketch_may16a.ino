long long tim;

void setup() {
  Serial.begin(9600);
  tim = millis();
}

int a = 3, b = 13;
void loop() {
  //if(a != b) a += (0.5 - (a > b))*2;
  tim = millis();
  //Serial.println(int(tim));
  delay(1);
}
