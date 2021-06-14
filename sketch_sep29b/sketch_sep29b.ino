void setup() {
  Serial.begin(9600);

}
int maxx = 0, minn = 2000;
int a, n = 0;;
void loop() {
  a = analogRead(A0);
  if(a > 578) {
    n++;
    Serial.print("TOUCH"); Serial.println(a);
    while(a > 560) {
      a = analogRead(A0);
    }
    Serial.println(a); Serial.print("  NUMS: "); Serial.println(n);
  }
  delay(3);
}

//MIN: 578 MAX: 657
