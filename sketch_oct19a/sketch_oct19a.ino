#include <Servo.h>
Servo my;
void setup() {
 
my.attach(9);
}

void loop() {
  my.write(0);

}
