#include <stdio.h>
#include <string.h>

int main(void) {
  char buf[255];
  int ch;
  char *p;

  if (fgets(buf, sizeof(buf), stdin)) {
    p = strchr(buf, '\n');
    if (p) {
      *p = '\0';
    } else {
      while (((ch = getchar()) != '\n') && !feof(stdin) && !ferror(stdin)) {
      }
    }
  } else {
    // 123
  }

  return 0;
}
