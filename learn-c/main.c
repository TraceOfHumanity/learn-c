#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  char *str = "Alex TH 2000000000";
  char name[10], title[10];
  int age = 0, ret = 0;

  ret = sscanf(str, "%s %s %d", name, title, &age);

  printf("Name: %s\n", name);
  printf("Title: %s\n", title);
  printf("Age: %d\n", age);

  return 0;
}