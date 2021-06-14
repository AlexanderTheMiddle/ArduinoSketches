void setup() {
  pinMode(7, OUTPUT);
  Serial.begin(9600);// put your setup code here, to run once:

}
int a;
void loop() {
  while(Serial.available()) {
    a = Serial.read();
    Serial.println(a);
    if (a == 49) {
      for(int i = 0; i < 5; i++) {
        Serial.print("ON ");
        digitalWrite(7, 0);
      
      delay(20);
      Serial.println("OFF");
      digitalWrite(7, 1);
      
      delay(5);
      }
      a = 0;
    }
  }
  
 
}
