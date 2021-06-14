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
RF24 radio(10, 9); // "создать" модуль на пинах 9 и 10 Для Уно
//RF24 radio(9,53); // для Меги
byte address[][6] = {"1Node","2Node","3Node","4Node","5Node","6Node"};  //возможные номера труб
byte recieved[20];
Servo a, elevator, turn;
void setup(){
  a.attach(8);
  elevator.attach(3);
  turn.attach(4);

  Serial.begin(115200); //открываем порт для связи с ПК
  radio.begin(); //активировать модуль
  radio.setAutoAck(1);         //режим подтверждения приёма, 1 вкл 0 выкл
  radio.setRetries(0,15);     //(время между попыткой достучаться, число попыток)
  radio.enableAckPayload();    //разрешить отсылку данных в ответ на входящий сигнал
  radio.setPayloadSize(32);     //размер пакета, в байтах
  radio.openReadingPipe(1,address[5]);      //хотим слушать трубу 0
  radio.setChannel(0x60);  //выбираем канал (в котором нет шумов!)
  radio.setPALevel (RF24_PA_MAX); //уровень мощности передатчика. На выбор RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  radio.setDataRate (RF24_250KBPS); //скорость обмена. На выбор RF24_2MBPS, RF24_1MBPS, RF24_250KBPS
  //должна быть одинакова на приёмнике и передатчике!
  //при самой низкой скорости имеем самую высокую чувствительность и дальность!!
  
  radio.powerUp(); //начать работу
  radio.startListening();  //начинаем слушать эфир, мы приёмный модуль
}
int throttle, elevation, turning;
int lastthrottle = 1, lastelevation = 1, lastturning = 1;
void loop() {
    byte pipeNo;                          
    while( radio.available(&pipeNo)){    // слушаем эфир со всех труб
      radio.read( &recieved, sizeof(recieved) );         // чиатем входящий сигнал
   }
   throttle = recieved[4]*255 + recieved[5];
   elevation = recieved[2]*255 + recieved[3];
   turning = recieved[0]*255 + recieved[1];
   if(recieved[6] == 0 && recieved[7] == 0 && recieved[8] == 0 && recieved[9] == 0) {
    throttle = lastthrottle;
    elevation = lastelevation;
    turning = lastturning;
   }
   else {
    lastthrottle = throttle;
    lastelevation = elevation;
    lastturning = turning;
   }
   throttle = map(throttle, 0, 1023, 800, 2300);
   elevation = map(elevation, 0, 1023, 180, 0);
   turning = map(turning, 0, 1023, 0, 180);
   a.writeMicroseconds(throttle);
   elevator.write(elevation);
   turn.write(turning);
   delay(20);
   //serial feedback
   for(int i = 0; i < 6; i++) {
    Serial.print(recieved[i*2]*255 + recieved[i*2 + 1]);
    Serial.print(" ");
  }
  for(int i = 2; i < 6; i++) {
    Serial.print(recieved[10+i]);
    Serial.print(" ");
  }
  Serial.print(recieved[16] - recieved[16]*2*recieved[17]);
    Serial.print(" ");
    Serial.print(recieved[18] - recieved[18]*2*recieved[19]);
    Serial.print(" ");
  Serial.println(" ");
  
}
