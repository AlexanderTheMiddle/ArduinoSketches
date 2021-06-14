class Queue {
  public:
    float emptyValue = 0.00010100203;
    int queueSize = 0, rearPointer = 0, frontPointer = 0;
    float myQueue[100];
    
    Queue(int queueSize_) {
      queueSize = queueSize_;
      for (int i = 0; i < queueSize; i++) {
        myQueue[i] = emptyValue;
      }
    }

    Queue(int queueSize_, float emptyValue_) {
      queueSize = queueSize_;
      emptyValue = emptyValue_;
      for (int i = 0; i < queueSize; i++) {
        myQueue[i] = emptyValue;
      }
    }

    void enQueue(float dataItem) {
      if (!Full()) {
        myQueue[rearPointer] = dataItem;
        rearPointer = (rearPointer+1)%queueSize;
      } else Serial.println("Already Full ");
    }

    void deQueue() {
      if (!Empty()) {
        myQueue[frontPointer] = emptyValue;
        frontPointer = (frontPointer+1)%queueSize;
      } else Serial.println("Already Empty ");
    }
  /*
    float deQueue(int r) {
      float returnData = myQueue[frontPointer];
      if (!isEmpty()) {
        myQueue[frontPointer] = emptyValue;
        frontPointer = (frontPointer+1)%queueSize;
      } else Serial.println("Already Empty ");
      return returnData;
    }
  */
    boolean Full() {
      boolean full = true;
      for (int i = 0; i < queueSize; i++) {
        if (myQueue[i] == emptyValue) full = false;
      }
      return full;
    }

    boolean Empty() {
      boolean empty = true;
      for (int i = 0; i < queueSize; i++) {
        if (myQueue[i] != emptyValue) empty = false;
      }
      return empty;
    }

    void Reset() {
      rearPointer = 0;
      frontPointer = 0;
      for (int i = 0; i < queueSize; i++) {
        myQueue[i] = emptyValue;
      }
    }

    float maximum() {
      float maximum = 0;
      for (int i = 0; i < queueSize; i++) {
        if(myQueue[i] > maximum) maximum = myQueue[i];
      }
      return maximum;
    }

    float minimum() {
      float minimum = 1023;
      for (int i = 0; i < queueSize; i++) {
        if(myQueue[i] < minimum && myQueue[i] != emptyValue) minimum = myQueue[i];
      }
      return minimum;
    }
    
    void Fill(float v) {
      rearPointer = 0;
      frontPointer = 0;
      for (int i = 0; i < queueSize; i++) {
        myQueue[i] = v;
      }
    }

    float sum() {
      if (!Empty()) {
        float summ = 0;
        for (int i = 0; i < queueSize; i++) {
          if (myQueue[i] != emptyValue) {
            summ+=myQueue[i];
          }
        }
        return summ;
      } else return emptyValue;
    }
    
    float average() {
      if (!Empty()) {
        int n = 0;
        float summ = 0;
        for (int i = 0; i < queueSize; i++) {
          if (myQueue[i] != emptyValue) {
            n++;
            summ+=myQueue[i];
          }
        }
        return summ/n;
      } else return emptyValue;
    }
};

#include <Servo.h>

Servo right, left;
Queue brainData(30);

void setup() {
  Serial.begin(9600);
  
  right.attach(6);
  left.attach(5);
  pinMode(7, INPUT_PULLUP);
  
  brainData.Fill(0);
}

int servoMin = 0, servoMax = 120, servoValue = 90;
int treshold = 600;

void loop() {
  if (brainData.Full()) brainData.deQueue();
  brainData.enQueue(analogRead(A0));
  
  if(!digitalRead(7)) servoValue = constrain(map(brainData.average(), 820, 0, servoMin, servoMax), 0, 180);
  else servoValue = max(servoMin, servoMax*int(brainData.average() < treshold));
  
  right.write(servoValue);
  left.write(180 - servoValue);
  
  Serial.println(analogRead(A0));
  //Serial.println(digitalRead(7));
  delay(10);

}
