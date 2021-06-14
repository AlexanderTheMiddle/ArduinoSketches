#include <Keyboard.h>
#include <Mouse.h>
/*   Данный скетч делает следующее: передатчик (TX) отправляет массив
     данных, который генерируется согласно показаниям с кнопки и с
     двух потенциомтеров. Приёмник (RX) получает массив, и записывает
     данные на реле, сервомашинку и генерирует ШИМ сигнал на транзистор.
    by AlexGyver 2016
*/

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"

RF24 radio(9, 10); // "создать" модуль на пинах 9 и 10 Для Уно
//RF24 radio(9,53); // для Меги

byte recieved_info[4];

byte address[][6] = {"1Node", "2Node", "3Node", "4Node", "5Node", "6Node"}; //возможные номера труб

void setup() {
  Serial.begin(9600); //открываем порт для связи с ПК
  Mouse.begin();

  radio.begin(); //активировать модуль
  radio.setAutoAck(1);         //режим подтверждения приёма, 1 вкл 0 выкл
  radio.setRetries(0, 15);    //(время между попыткой достучаться, число попыток)
  radio.enableAckPayload();    //разрешить отсылку данных в ответ на входящий сигнал
  radio.setPayloadSize(32);     //размер пакета, в байтах
  radio.openReadingPipe(1, address[0]);     //хотим слушать трубу 0
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
boolean connectedToTX = false;
float potX, potY;
void loop() {
  byte pipeNo;
  while ( radio.available(&pipeNo)) {  // слушаем эфир со всех труб
    radio.read( &recieved_info, sizeof(recieved_info) );         // чиатем входящий сигнал
  }
  potX = recieved_info[0] * 255 + recieved_info[1];
  potY = recieved_info[2] * 255 + recieved_info[3];
  Serial.print(potX);
  Serial.print(" ");
  Serial.println(potY);
  if (potX != 0 || potY != 0) connectedToTX = true;
  if (connectedToTX) {
    float mi = 1023 / 4, ma = 1023 * 3 / 4;
    Mouse.move(int(potX > ma) - int(potX < mi), 0 - int(potY > ma) + int(potY < mi), 0);
    delay(1);
  }

}
