//Include HCSR04 Library
#include <HCSR04.h>

//Include Wire Library
#include <Wire.h>

//Include Oled SSD1306 Library
#include <ACROBOTIC_SSD1306.h>


void displayMessage()
{
  
  // Set cursor position, line 4 0th character
  oled.setTextXY(4,0);  
  
 //Show the measurement           
  oled.putString("Test");   

  // Set cursor position, line 6 0th character       
  oled.setTextXY(6,0);   

  //Show the Warning Message          
  oled.putString("OBJ DETECTED"); 
  
}

void setup()
{
  
  //Initialize serial port to send messages
  Serial.begin(9600);
  
  //Initiate the Wire library and join the I2C bus as a master or slave
  Wire.begin();  

  // Initialze SSD1306 OLED display
  oled.init();      

  // Clear screen                
  oled.clearDisplay();     
     
  oled.setTextXY(0,0);               
  oled.putString("OBJECTS");      
  oled.setTextXY(1,0);           
  oled.putString("DETECTION");     
  oled.setTextXY(4,0);  

  //Show the measurement on the Oled           
  oled.putString("Seee");  
  delay(5000);       
}

void loop()
{

  
     displayMessage();
  
}
