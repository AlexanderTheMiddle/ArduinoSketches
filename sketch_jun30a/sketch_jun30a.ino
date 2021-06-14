#include <Servo.h>

Servo a[3];

int N = 3, del = 20;
double A = 1.0, slow = 1.0, spid = 1.0, angle[3], x0, x, y0, y, d = 0.0, theta = 0.0, l[3] = {1.675, 1.625, 1.675};
//inicialise!!!!!
// l divide by 4 
void setup() {
  Serial.begin(9600);
  for(int i = 0; i < N; i++) {
    a[i].attach(8+i);
  }
  for(int i = 0; i < N; i++) {
    a[i].write(120);
  }
  delay(1000);
  for(int i = 0; i < N; i++) {
    a[i].write(60);
  }
  delay(1000);
  
}

void loop() {
  x0 = 0; y0 = 0; x = 0;
  for(int i = 0; i < N; i++) {
    for(; d < l[i]*l[i]; x++) {
      y = sin(0.0174533*(x-theta)/slow)*A;
      d = (x - x0)*(x - x0) + (y - y0)*(y - y0);
    }
    angle[i] = atan((y - y0)/(x - x0));
    x0 = x; y0 = y;
    Serial.print("YES");
  }
  
  angle[2] -= angle[1];
  angle[1] -= angle[0];

  angle[0] = 90 - angle[0];
  angle[1] = 90 + angle[1];
  angle[2] = 90 + angle[2];

  for(int i = 0; i < N; i++) {
    a[i].write(angle[i]);
    Serial.print(angle[i]); Serial.print(" ");
  }
  Serial.println(" ");



  theta += spid;
  delay(del);
}
