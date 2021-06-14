void timerFunction() {
  nowMicros+=100;
}

int amountOfON() {
  int sum = 0;
  for (int i = 0; i < NUM_LEDS; i++) {
    if(isON[i]) sum++;
  }
  return sum;
}
