#include <Mouse.h>

/*   Данный скетч делает следующее: передатчик (TX) отправляет массив
 *   данных, который генерируется согласно показаниям с кнопки и с 
 *   двух потенциомтеров. Приёмник (RX) получает массив, и записывает
 *   данные на реле, сервомашинку и генерирует ШИМ сигнал на транзистор.
    by AlexGyver 2016
*/

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include <Servo.h>

RF24 radio(9,10); // "создать" модуль на пинах 9 и 10 Для Уно
//RF24 radio(9,53); // для Меги

byte recieved_info[5];

byte address[][6] = {"1Node","2Node","3Node","4Node","5Node","6Node"};  //возможные номера труб

void setup(){
  Serial.begin(9600); //открываем порт для связи с ПК
  Mouse.begin();

  radio.begin(); //активировать модуль
  radio.setAutoAck(1);         //режим подтверждения приёма, 1 вкл 0 выкл
  radio.setRetries(0,15);     //(время между попыткой достучаться, число попыток)
  radio.enableAckPayload();    //разрешить отсылку данных в ответ на входящий сигнал
  radio.setPayloadSize(32);     //размер пакета, в байтах
  radio.openReadingPipe(1,address[0]);      //хотим слушать трубу 0
  radio.setChannel(0x60);  //выбираем канал (в котором нет шумов!)
  radio.setPALevel (RF24_PA_MAX); //уровень мощности передатчика. На выбор RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  radio.setDataRate (RF24_250KBPS); //скорость обмена. На выбор RF24_2MBPS, RF24_1MBPS, RF24_250KBPS
  //должна быть одинакова на приёмнике и передатчике!
  //при самой низкой скорости имеем самую высокую чувствительность и дальность!!
  Serial.println("Star powerup");
  radio.powerUp(); //начать работу
  Serial.println("Start listen");
  radio.startListening();  //начинаем слушать эфир, мы приёмный модуль
}

void loop() {
    byte pipeNo;                          
    while( radio.available(&pipeNo)){    // слушаем эфир со всех труб
      radio.read( &recieved_info, sizeof(recieved_info) );         // чиатем входящий сигнал
   }
   float potX = recieved_info[0]*255 + recieved_info[1];
   float potY = recieved_info[2]*255 + recieved_info[3];
   boolean pressed = recieved_info[4];
   Serial.print(potX);
   Serial.print(" ");
   Serial.println(potY);
   if(potX != 0 || potY != 0) {
    float maxx = 2;
     float xSpeed = map(potX, 0, 1006, -maxx, maxx);
     float ySpeed = map(potY, 0, 494*2, maxx, -maxx);
     Mouse.move(xSpeed, ySpeed, 0);
     if(pressed) {
      Mouse.press();
      delay(15);
     }
     if(!pressed) {
      Mouse.release();
     }
     
     delay(1);
   
   }
}
