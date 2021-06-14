int transistorPin = 2;
boolean state = false;

void setup() {
  Serial.begin(9600);

  pinMode(transistorPin, OUTPUT);
  digitalWrite(transistorPin, state);

}

long duration = 1000;
long spacing = 6000;
long lastTimeChanged = 0;

int minDuration = 1000, maxDuration = 3000;
int minSpacing = 1000, maxSpacing = 6000;

void loop() {
  if((!state && millis() - lastTimeChanged > spacing) || (state && millis() - lastTimeChanged > duration)) {
    lastTimeChanged = millis();
    duration = int(random(minDuration, maxDuration));
    spacing = int(random(minSpacing, maxSpacing));
    state = !state;
    digitalWrite(transistorPin, state);
  }
  Serial.print(duration);
  Serial.print(" ");
  Serial.print(spacing);
  Serial.print(" ");
  Serial.println(state);
}
