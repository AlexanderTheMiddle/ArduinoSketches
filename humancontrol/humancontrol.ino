
 
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

#define rfone 10
#define rftwo 9
RF24 radio(rfone, rftwo); // "создать" модуль на пинах 9 и 10 Для Уно
//RF24 radio(9,53); // для Меги
byte address[][6] = {"1Node","2Node","3Node","4Node","5Node","6Node"};  //возможные номера труб
byte recieved[4];

void setup(){


  
  Serial.begin(115200); //открываем порт для связи с ПК
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
  
  radio.powerUp(); //начать работу
  radio.startListening();  //начинаем слушать эфир, мы приёмный модуль

  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);

}


void loop() {
    byte pipeNo;                          
    while( radio.available(&pipeNo)){    // слушаем эфир со всех труб
      radio.read( &recieved, sizeof(recieved) );         // чиатем входящий сигнал
    }

    float potX = recieved[0]*255 + recieved[1];
    float potY = recieved[2]*255 + recieved[3];
    Serial.print(potX);
    Serial.print(" ");
    Serial.println(potY);

    if(potX < 1023*1/4 && potY!=0) {
      digitalWrite(5, HIGH);
      digitalWrite(4, LOW);
    }
    else if(potX > 1023*3/4 && potY!=0) {
      digitalWrite(4, HIGH);
      digitalWrite(5, LOW);
    }
    else {
      digitalWrite(4, LOW);
      digitalWrite(5, LOW);
    }

    
}
