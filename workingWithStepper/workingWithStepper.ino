// Видеообзоры и уроки работы с ARDUINO на YouTube-канале IOMOIO: https://www.youtube.com/channel/UCmNXABaTjX_iKH28TTJpiqA

#include <CustomStepper.h>            // Подключаем библиотеку управления шаговым двигателем. По умолчанию настроена на двигатель 28BYJ-48-5V
CustomStepper stepper(10, 11, 12, 13);  // Указываем пины, к которым подключен драйвер шагового двигателя

int example = 1;                      // Переменная для демонстрации работы, отвечающая за смену режимов

void setup()
{
  stepper.setRPM(12);                 // Устанавливаем кол-во оборотов в минуту
  stepper.setSPR(4075.7728395);       // Устанавливаем кол-во шагов на полный оборот. Максимальное значение 4075.7728395
}
int timerr, del = 1000;
void loop() {
  stepper.setRPM(17);
  if (stepper.isDone()) {
    stepper.setDirection(CW);
    //stepper.rotateDegrees(90);
    stepper.rotate(2);
  }
  stepper.run();
  stepper.setRPM(10);
  if (stepper.isDone()) {
    stepper.setDirection(CW);
    //stepper.rotateDegrees(90);
    stepper.rotate(2);
  } 
  /*
  if (stepper.isDone()) {
    stepper.setDirection(STOP);
  }
  delay(1000);
  
  if (stepper.isDone()) {
    stepper.setDirection(CW);
    stepper.rotateDegrees(90);
  }
  stepper.run(); 
  
  if (stepper.isDone()) {
    stepper.setDirection(STOP);
  }
  delay(1000);
  */
}
