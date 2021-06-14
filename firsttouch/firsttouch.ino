#include <Adafruit_GFX.h>
#include <MCUFRIEND_kbv.h>
MCUFRIEND_kbv tft;
#include <TouchScreen.h>
//#include "bitmap_mono.h" // when you want to display a bitmap image from library
//#include "bitmap_RGB.h" // when you want to display a bitmap image from library
#include "Fonts/FreeSans9pt7b.h"    // when you want other fonts
#include "Fonts/FreeSans12pt7b.h" // when you want other fonts
#include "Fonts/FreeSerif12pt7b.h" // when you want other fonts
#include "FreeDefaultFonts.h" // when you want other fonts 
#include "SPI.h"  // using sdcard for display bitmap image
#include "SD.h"
#define MINPRESSURE 200
#define MAXPRESSURE 1000

// ALL Touch panels and wiring is DIFFERENT
// copy-paste results from TouchScreen_Calibr_native.ino
const int XP = 8, XM = A2, YP = A3, YM = 9; //240x320 ID=0x9341
const int TS_LEFT = 930, TS_RT = 94, TS_TOP = 66, TS_BOT = 892;

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300);

Adafruit_GFX_Button on_btn, off_btn;

int pixel_x, pixel_y;     //Touch_getXY() updates global vars
bool Touch_getXY(void)
{
  TSPoint p = ts.getPoint();
  pinMode(YP, OUTPUT);      //restore shared pins
  pinMode(XM, OUTPUT);
  digitalWrite(YP, HIGH);   //because TFT control pins
  digitalWrite(XM, HIGH);
  bool pressed = (p.z > MINPRESSURE && p.z < MAXPRESSURE);
  if (pressed) {
    pixel_x = map(p.x, TS_LEFT, TS_RT, 0, tft.width()); //.kbv makes sense to me
    pixel_y = map(p.y, TS_TOP, TS_BOT, 0, tft.height());
  }
  return pressed;
}

#define BLACK 0x0000
#define NAVY 0x000F
#define DARKGREEN 0x03E0
#define DARKCYAN 0x03EF
#define MAROON 0x7800
#define PURPLE 0x780F
#define OLIVE 0x7BE0
#define LIGHTGREY 0xC618
#define DARKGREY 0x7BEF
#define BLUE 0x001F
#define GREEN 0x07E0
#define CYAN 0x07FF
#define RED 0xF800
#define MAGENTA 0xF81F
#define YELLOW 0xFFE0
#define WHITE 0xFFFF
#define ORANGE 0xFD20
#define GREENYELLOW 0xAFE5
#define PINK 0xF81F

int16_t Width, Height;
int16_t x, y;

void setup(void) {
  Serial.begin(9600);
  uint16_t ID = tft.readID();
  Width = tft.width();
  Height = tft.height();

  Serial.print("TFT ID = 0x");
  Serial.println(ID, HEX);
  Serial.println("Calibrate for your Touch Panel");
  if (ID == 0xD3D3) ID = 0x9486; // write-only shield
  tft.begin(ID);
  tft.setRotation(0);            //PORTRAIT
  tft.fillScreen(BLACK);
  on_btn.initButton(&tft,  60, 200, 100, 40, WHITE, CYAN, BLACK, "ON", 2);
  off_btn.initButton(&tft, 180, 200, 100, 40, WHITE, CYAN, BLACK, "OFF", 2);

  x = Width/2;
  y = Height/2;
}

/* two buttons are quite simple
*/
void loop(void) {
  //tft.fillScreen(BLACK);
  tft.setTextSize(3);
  tft.setCursor(x,y);
  tft.setTextColor(BLACK);
  tft.print("HELLO");
  x = (x+3)%Width;
  y = (y+1)%Height;
  tft.setCursor(x,y);
  tft.setTextColor(GREEN);
  tft.print("HELLO");
  Serial.println(tft.readPixel(Width/2, Height/2));
  delay(10);
  /*
    bool down = Touch_getXY();
    on_btn.press(down && on_btn.contains(pixel_x, pixel_y));
    off_btn.press(down && off_btn.contains(pixel_x, pixel_y));
    if (on_btn.justReleased())
    on_btn.drawButton();
    if (off_btn.justReleased())
    off_btn.drawButton();
    if (on_btn.justPressed()) {
    tft.fillScreen(BLACK);
    tft.fillRect(40, 80, 160, 80, GREEN);
    off_btn.drawButton(true);
    on_btn.drawButton(true);
    }
    if (off_btn.justPressed()) {
    tft.fillScreen(CYAN);
    tft.fillCircle(100, 100, 60, RED);
    off_btn.drawButton(true);
    on_btn.drawButton(true);
    }
  */
}
