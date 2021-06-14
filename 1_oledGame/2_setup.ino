
void setup() {
  Serial.begin(9600);

  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Address 0x3D for 128x64
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  // Show initial display buffer contents on the screen --
  // the library initializes this with an Adafruit splash screen.
  display.clearDisplay();
  
  pinMode(leftPin, INPUT_PULLUP);
  pinMode(upPin, INPUT_PULLUP);
  pinMode(rightPin, INPUT_PULLUP);
  pinMode(downPin, INPUT_PULLUP);
  pinMode(okPin, INPUT_PULLUP); 
}
