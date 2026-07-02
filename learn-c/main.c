#include <stdio.h>

int main(void) {
  short int w1 = 154;
  short int result = 0;

  result = ~w1;
  printf("%d", result);

  return 0;
}
