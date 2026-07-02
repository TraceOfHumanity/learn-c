#include <stdio.h>

int main(void) {
  short int w1 = 25;
  short int w2 = 77;

  w1 = w1 ^ w2;
  w2 = w1 ^ w2;
  w1 = w1 ^ w2;

  return 0;
}
