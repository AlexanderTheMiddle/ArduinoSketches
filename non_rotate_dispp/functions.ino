  int ii[8] = { 0, 1, 7, 2, 3, 4, 5, 6};
/*
  void show_number(int dec) {
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
*/
