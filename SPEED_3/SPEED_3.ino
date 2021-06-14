

#define Speed A4



void setup() {
  Serial.begin(9600);
  pinMode(Speed, INPUT);
  
}
void loop() {
  
  int sped = map(analogRead(Speed), 272, 756, 120, 255);
  //if ( angle < 11) angle = 11;
  //if ( angle > 69) angle = 69;
 //locot_servo.write(angle);
 
 
 Serial.println(sped);
 //delay(3);
  
  
}

// для сервы плеча
// ) 272 755
