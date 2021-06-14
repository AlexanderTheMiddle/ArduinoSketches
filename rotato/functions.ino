
//int ii[8] = { 0, 1, 7, 2, 3, 4, 5, 6};


void one_by_one(int a) { /////////////////////один за другим
for(int j = 0; j < 8; j++) {
  
  for(int i = 7; i > -1; i--) {
    digitalWrite(thisbyte, ii[i] == j);
    delayMicroseconds(3);
    digitalWrite(savebyte, 1);
    delayMicroseconds(3);
    digitalWrite(savebyte, 0);
    delayMicroseconds(3);
  }
  digitalWrite(showbytes, 1);
  delayMicroseconds(3);
  digitalWrite(showbytes, 0);
  delayMicroseconds(3);
  delay(a);
}
for(int i = 7; i > -1; i--) {
    digitalWrite(thisbyte, 0);
    delayMicroseconds(3);
    digitalWrite(savebyte, 1);
    delayMicroseconds(3);
    digitalWrite(savebyte, 0);
    delayMicroseconds(3);
  }
  digitalWrite(showbytes, 1);
  delayMicroseconds(3);
  digitalWrite(showbytes, 0);
}

void light_up(int a, int b) {/////////////////////определённый на определённое время
  for(int i = 7; i > -1; i--) {
    digitalWrite(thisbyte, ii[i] == a);
    delayMicroseconds(3);
    digitalWrite(savebyte, 1);
    delayMicroseconds(3);
    digitalWrite(savebyte, 0);
    delayMicroseconds(3);
  }
  digitalWrite(showbytes, 1);
  delayMicroseconds(3);
  digitalWrite(showbytes, 0);
  delayMicroseconds(3);
  
  delay(b);
  
  for(int i = 7; i > -1; i--) {
    digitalWrite(thisbyte, 0);
    delayMicroseconds(3);
    digitalWrite(savebyte, 1);
    delayMicroseconds(3);
    digitalWrite(savebyte, 0);
    delayMicroseconds(3);
  }
  digitalWrite(showbytes, 1);
  delayMicroseconds(3);
  digitalWrite(showbytes, 0);
  delayMicroseconds(3);
}


void light_up_all(int b) {/////////////////////зажечь все
  for(int i = 7; i > -1; i--) {
    digitalWrite(thisbyte, 1);
    delayMicroseconds(3);
    digitalWrite(savebyte, 1);
    delayMicroseconds(3);
    digitalWrite(savebyte, 0);
    delayMicroseconds(3);
  }
  digitalWrite(showbytes, 1);
  delayMicroseconds(3);
  digitalWrite(showbytes, 0);
  delayMicroseconds(3);
  
  delay(b);
  
  for(int i = 7; i > -1; i--) {
    digitalWrite(thisbyte, 0);
    delayMicroseconds(3);
    digitalWrite(savebyte, 1);
    delayMicroseconds(3);
    digitalWrite(savebyte, 0);
    delayMicroseconds(3);
  }
  digitalWrite(showbytes, 1);
  delayMicroseconds(3);
  digitalWrite(showbytes, 0);
  delayMicroseconds(3);
}


void all_off() {/////////////////////выключить все
  for(int i = 7; i > -1; i--) {
    digitalWrite(thisbyte, 0);
    delayMicroseconds(3);
    digitalWrite(savebyte, 1);
    delayMicroseconds(3);
    digitalWrite(savebyte, 0);
    delayMicroseconds(3);
  }
  digitalWrite(showbytes, 1);
  delayMicroseconds(3);
  digitalWrite(showbytes, 0);
  delayMicroseconds(3);
}


void cout(int a) {/////////////////////cout
  Serial.println(a);
}



void show_number(int dec) {/////////////////////показать двоичное число
  int bin = 0, j = 0;
  String sss = "";
  for(; dec > 0; j++) {
    bin += (dec%2) * pow(10.0, j);
    dec /= 2;
  }
  for(j = 8; j > 0; j--) {  
    sss += char( (bin / int(pow(10, j - 1))) % 10 + int('1') - 1); 
  }
  for(int i = 7; i > -1; i--) {
    digitalWrite(thisbyte, int(sss[ii[i]]) - int('1') + 1);
    delayMicroseconds(3);
    digitalWrite(savebyte, 1);
    delayMicroseconds(3);
    digitalWrite(savebyte, 0);
    delayMicroseconds(3);
  }
  digitalWrite(showbytes, 1);
  delayMicroseconds(3);
  digitalWrite(showbytes, 0);
  delayMicroseconds(3);
}


void show_bytes(int q, int dela) {/////////////////////показать биты
  for(int i = 7; i > -1; i--) {
    digitalWrite(thisbyte, bytes[q][ii[i]]);
    delayMicroseconds(3);
    digitalWrite(savebyte, 1);
    delayMicroseconds(3);
    digitalWrite(savebyte, 0);
    delayMicroseconds(3);
  }
  digitalWrite(showbytes, 1);
  delayMicroseconds(3);
  digitalWrite(showbytes, 0);
  delayMicroseconds(3);
  delay(dela);
  all_off();
}
