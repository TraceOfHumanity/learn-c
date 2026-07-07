#include <stdio.h>

int main(void)
{
  char string[100];
  sprintf(string, "hello, this is the number: %d", 55);
  puts(string);
  return 0;
}
