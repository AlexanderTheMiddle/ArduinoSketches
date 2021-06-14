void setup() {
  Serial.begin(9600);
 // pinMode(A0, INPUT_PULLUP);
 //delay(3000);
}
int av = 0;
long long sum = 0;
int i = 1;
boolean nestarted = 1;
int j = 0;
int timer = 0;
int timer2 = 0;
boolean sho = 0;
void loop() {
  if(analogRead(A0) > 150 && j > 299) {
    if(nestarted) timer = millis();
    sum += analogRead(A0);
    if(av = 199) {
      sho = 1;
      timer2 = millis();
    }
    
  j--;
  av = sum / i;
  i++;
  }
  Serial.print(analogRead(A0));
  Serial.print("  Среднее: ");
  Serial.println(av);
  if(sho) {
      pr("  Time ");
      Serial.println(timer2-timer);
    }
  j++;
  delay(10);
}

int pr(String a) {
  Serial.print(a);
}
