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
      }
    }

    void deQueue() {
      if (!Empty()) {
        myQueue[frontPointer] = emptyValue;
        frontPointer = (frontPointer+1)%queueSize;
      }
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

    float sumOfLessThan(float mini) {
      if (!Empty()) {
        float summ = 0;
        for (int i = 0; i < queueSize; i++) {
          if (myQueue[i] != emptyValue && myQueue[i] < mini) {
            summ+=myQueue[i];
          }
        }
        return summ;
      } else return emptyValue;
    }

    float sumOfMoreThan(float maxi) {
      if (!Empty()) {
        float summ = 0;
        for (int i = 0; i < queueSize; i++) {
          if (myQueue[i] != emptyValue && myQueue[i] > maxi) {
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

    float averageOfLessThan(float mini) {
      if (!Empty()) {
        int n = 0;
        float summ = 0;
        for (int i = 0; i < queueSize; i++) {
          if (myQueue[i] != emptyValue && myQueue[i] < mini) {
            n++;
            summ+=myQueue[i];
          }
        }
        return summ/n;
      } else return emptyValue;
    }

    float averageOfMoreThan(float maxi) {
      if (!Empty()) {
        int n = 0;
        float summ = 0;
        for (int i = 0; i < queueSize; i++) {
          if (myQueue[i] != emptyValue && myQueue[i] > maxi) {
            n++;
            summ+=myQueue[i];
          }
        }
        return summ/n;
      } else return emptyValue;
    }
    
};

Queue heartData(100);
int heartPin = A1;

void setup() {
  Serial.begin(9600);
  pinMode(1, OUTPUT);
  heartData.Fill(analogRead(heartPin));
}

void loop() {
  if (heartData.Full()) heartData.deQueue();
  heartData.enQueue(analogRead(heartPin));

  float minn = heartData.averageOfLessThan(heartData.minimum() + 0.5*(heartData.average()-heartData.minimum()));
  float maxx = heartData.averageOfMoreThan(heartData.maximum() - 0.5*(heartData.maximum()-heartData.average()));
  
    
  Serial.print(analogRead(A1));
  Serial.print(" ");
  Serial.print(heartData.averageOfLessThan(heartData.minimum() + 0.5*(heartData.average()-heartData.minimum())));
  Serial.print(" ");
  Serial.println(heartData.averageOfMoreThan(heartData.maximum() - 0.5*(heartData.maximum()-heartData.average())));
  
  analogWrite(3, constrain(map(analogRead(A1), minn, maxx, 0, 255), 0, 255));
  delay(10);
}
