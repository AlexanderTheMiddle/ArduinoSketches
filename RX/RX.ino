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

byte recieved_info[4];

Servo jawservo, updown, ebservo, bigservo;


byte address[][6] = {"1Node","2Node","3Node","4Node","5Node","6Node"};  //возможные номера труб

void setup(){
  delay(3000);
  Serial.begin(9600); //открываем порт для связи с ПК
  Serial.println("START AERIAL");
  //pinMode(plecho

  delay(3000);
  jawservo.attach(8);
  updown.attach(7);
  ebservo.attach(6);
  bigservo.attach(5);

  
  
  radio.begin(); //активировать модуль
  radio.setAutoAck(1);         //режим подтверждения приёма, 1 вкл 0 выкл
  radio.setRetries(0,15);     //(время между попыткой достучаться, число попыток)
  radio.enableAckPayload();    //разрешить отсылку данных в ответ на входящий сигнал
  radio.setPayloadSize(32);     //размер пакета, в байтах
Serial.println("6");
  radio.openReadingPipe(1,address[0]);      //хотим слушать трубу 0
  Serial.println("7");
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
  Serial.println("Start loop");
    byte pipeNo;                          
    while( radio.available(&pipeNo)){    // слушаем эфир со всех труб
      radio.read( &recieved_info, sizeof(recieved_info) );         // чиатем входящий сигнал
   }

   jawservo.write(recieved_info[0]);
   Serial.print("Челюсть ");
   Serial.print(recieved_info[0]);
   updown.write(recieved_info[1]);
   Serial.print("   верх/низ ");
   Serial.print(recieved_info[1]);
   ebservo.write(recieved_info[2]);
   Serial.print("   наклон ");
   Serial.print(recieved_info[2]);
   bigservo.write(recieved_info[3]);
   Serial.print("   поворот ");
   Serial.println(recieved_info[3]);
}
