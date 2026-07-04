#include <stdio.h>

int main(void) {
  int ch = '\0';
  FILE *fp;

  if ((fp = fopen("foo.c", "r"))) {
    ch = getc(fp);

    while ((ch = getc(fp)) != EOF) {
      printf("%c", ch);
    }
    printf("\n");
    fclose(fp);
  } else {
    printf("не вдалось відкрити файл\n");
  }
  return 0;
}
