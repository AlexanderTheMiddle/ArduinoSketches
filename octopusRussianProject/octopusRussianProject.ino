#include <Servo.h>
#include <SoftwareSerial.h>
#include <DFPlayer_Mini_Mp3.h>

SoftwareSerial mySerial(2, 3); // RX, TX

Servo myServo;

int servoPin = 5;
int servoGroundPin = 4;
int sensorPin = 6;

int numberOfTracks = 7;
long trackLengths[7] = {2900, 3400, 5800, 3300, 2400, 3800, 6700};
long lastTrackStartTime = 0;
int trackToPlay = -1;

void setup () {
  Serial.begin (9600);
  
  mySerial.begin (9600);
  mp3_set_serial (mySerial);  //set softwareSerial for DFPlayer-mini mp3 module 
  mp3_set_volume (30); //0 - 30

  myServo.attach(servoPin);
  pinMode(sensorPin, INPUT_PULLUP);

  pinMode(servoGroundPin, OUTPUT);
  digitalWrite(servoGroundPin, LOW);
 
}


float ang = 90;
float minAng = 0, maxAng = 180, dAng = 0.01;
boolean allowMove = false;

void loop () { 
  //myServo.write(0);

  
  if (allowMove) {
    digitalWrite(servoGroundPin, HIGH);
    ang+=dAng;
    if(ang >= maxAng || ang <= minAng) dAng*=-1;
    myServo.write(int(ang));
  }
  else digitalWrite(servoGroundPin, LOW);
  
  if(digitalRead(sensorPin)) {
    if(millis() - lastTrackStartTime > trackLengths[trackToPlay] || trackToPlay == -1) {
      startNewTrack(trackToPlay);
    }
    allowMove = true;
  }
  else {
    if(millis() - lastTrackStartTime > trackLengths[trackToPlay]) {
      mp3_pause();
      allowMove = false;
      lastTrackStartTime = 0;
      delay(500);
    }
  }
   /*
    mp3_play(3); 
   delay (10000);
   mp3_play(2); 
   delay (10000); 
   */
}

void startNewTrack(int lastTrack) {
  //mp3_pause();
  //delay(500);

  trackToPlay = (trackToPlay+1)%numberOfTracks;

  mp3_play(trackToPlay + 201);
  lastTrackStartTime = millis();
  delay(500);
}
/*
   mp3_play ();   //start play
   mp3_play (5);  //play "mp3/0005.mp3"
   mp3_next ();   //play next 
   mp3_prev ();   //play previous
   mp3_set_volume (uint16_t volume);  //0~30
   mp3_set_EQ (); //0~5
   mp3_pause ();
   mp3_stop ();
   void mp3_get_state ();   //send get state command
   void mp3_get_volume (); 
   void mp3_get_u_sum (); 
   void mp3_get_tf_sum (); 
   void mp3_get_flash_sum (); 
   void mp3_get_tf_current (); 
   void mp3_get_u_current (); 
   void mp3_get_flash_current (); 
   void mp3_single_loop (boolean state);  //set single loop 
   void mp3_DAC (boolean state); 
   void mp3_random_play (); 
 */
