#include <stdio.h>

int main(void) {
  short int w1 = 25;
  short int w2 = 77;
  short int temp = 0;

  temp = w1;
  w1 = w2;
  w2 = temp;


  return 0;
}
