#include <stdio.h>

void array(int size) {
  char alphabet[size];
  int x = 0;

  while (x < size) {
    alphabet[x] = 'a' + x;
    printf("%c \n", alphabet[x]);
    x++;
  }
}

int main(void) {
  array(5);
  return 0;
}
