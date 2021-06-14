float mean(float a[], int n) {
  float summ = 0;
  for(int i = dataSize - 1; i > dataSize - 1 - n; i--) {
    summ += a[i];
  }
  return summ/n;
}

void push(float a[], int p) {
  for(int j = p - 2; j > -1; j--) {
    a[j] = a[j+1];
  }
}
