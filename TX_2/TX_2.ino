
/*   Данный скетч делает следующее: передатчик (TX) отправляет массив
 *   данных, который генерируется согласно показаниям с кнопки и с 
 *   двух потенциомтеров. Приёмник (RX) получает массив, и записывает
 *   данные на реле, сервомашинку и генерирует ШИМ сигнал на транзистор.
    by AlexGyver 2016
*/

#include <SPI.h>          // библиотека для работы с шиной SPI
#include "nRF24L01.h"     // библиотека радиомодуля
#include "RF24.h"         // ещё библиотека радиомодуля

RF24 radio(9, 10); // "создать" модуль на пинах 9 и 10 Для Уно
//RF24 radio(9,53); // для Меги

byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"}; //возможные номера труб

byte to_send_info[2];

#define pot_P A0
#define pot_L A3
#define potmaxangle 255.0

void setup() {
  Serial.begin(9600); //открываем порт для связи с ПК

  radio.begin(); //активировать модуль
  radio.setAutoAck(1);         //режим подтверждения приёма, 1 вкл 0 выкл
  radio.setRetries(0, 15);    //(время между попыткой достучаться, число попыток)
  radio.enableAckPayload();    //разрешить отсылку данных в ответ на входящий сигнал
  radio.setPayloadSize(32);     //размер пакета, в байтах

  radio.openWritingPipe(address[0]);   //мы - труба 0, открываем канал для передачи данных
  radio.setChannel(0x60);  //выбираем канал (в котором нет шумов!)

  radio.setPALevel (RF24_PA_MAX); //уровень мощности передатчика. На выбор RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  radio.setDataRate (RF24_250KBPS); //скорость обмена. На выбор RF24_2MBPS, RF24_1MBPS, RF24_250KBPS
  //должна быть одинакова на приёмнике и передатчике!
  //при самой низкой скорости имеем самую высокую чувствительность и дальность!!

  radio.powerUp(); //начать работу
  radio.stopListening();  //не слушаем радиоэфир, мы передатчик
}

void loop() {
  //int angle_P = int((analogRead(pot_P)    ) / 1024.0 * potmaxangle);
  //int angle_L = int((analogRead(pot_L)   - 385 ) / 1024.0 * potmaxangle);
 // angle_P = constrain(angle_P, 0, 180);
 // angle_L = constrain(angle_L, 0, 180);

  //to_send_info[0] = angle_P;
  //to_send_info[1] = angle_L;

  to_send_info[0] = int( constrain(  int((analogRead(pot_P)    ) / 1024.0 * potmaxangle)   , 0, 180)  );
  to_send_info[1] = int(  constrain(   int((analogRead(pot_L)   - 385 ) / 1024.0 * potmaxangle)  , 0, 180) );
  
  radio.write(&to_send_info, sizeof(to_send_info));

}

// к углу плеча на врайте прибавить 20!!!!
