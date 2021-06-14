float vx = 0, vy = 0, g = -1.3, ax = 0.2*g;
float x0 = SCREEN_WIDTH/2, y0 = SCREEN_HEIGHT/2;
float x = SCREEN_WIDTH/2, y = SCREEN_HEIGHT/3;
float r = SCREEN_HEIGHT/3, alpha = 0;
float floorHeight = SCREEN_HEIGHT*2/3;
boolean butReleased[5] = {true, true, true, true, true};
boolean onTheGround = false;
float  pl = 0;
float PER;
void loop() {
  /*
    display.clearDisplay();
    display.drawCircle(display.width()/2, display.height()/2, map(analogRead(rotorPin), 0, 1024, 0, display.height()/2), SSD1306_WHITE);
    display.display();
    delay(10);
    */
    //alpha = map(analogRead(rotorPin), 1023, 0, 45-0, 45-270);
    //x = x0 + r*cos(radians(alpha));
    //y = y0 + r*sin(radians(alpha));
    PER = map(analogRead(rotorPin), 0, 1023, 1, 10);
    Serial.println(PER);
    physics();
    display.clearDisplay();
    display.drawLine(0, floorHeight, SCREEN_WIDTH, floorHeight, SSD1306_WHITE);
    onTheGround = false;
    if( y + PLAYER_HEIGHT/2 + 2 >= floorHeight) {
      y = floorHeight - PLAYER_WIDTH/2 - 2;
      onTheGround = true;
    }
    display.drawBitmap(x - PLAYER_WIDTH/2, y - PLAYER_HEIGHT/3, playerBit[int(pl/PER)%2], uint8_t(PLAYER_WIDTH), uint8_t(PLAYER_HEIGHT), SSD1306_WHITE);
    pl++;
    display.display();

    Serial.println("");
    for(int i = 0; i < 5; i++) {
      if(!digitalRead(pins[i]) && (butReleased[i] || i == 0 || i == 2) && onTheGround) {
        delay(10);
        if(!digitalRead(pins[i]) && (butReleased[i] || i == 0 || i == 2)) {
          butReleased[i] = false;
          if(i == 0) {
            vx = -3;
            //vy = 0;
          }
          if(i == 1) {
            //vx = 0;
            vy = -6;
          }
          if(i == 2) {
            vx = 3;
            //vy = 0;
          }
          if(i == 3) {
            //vx = 0;
            vy = 6;
          }
          if(i == 4) {
            vx = 0;
            vy = 0;
          }
        }
      }
      if(digitalRead(pins[i])) butReleased[i] = true;
    }
}
