#include <stdio.h>
#include <stdlib.h>

int main(void) {
  FILE *f = NULL;
  char ch[100];

  if ((f = fopen("./foo.c", "r+")) == NULL) {
    printf("Cannot open the file...");
    exit(1);
  }

  for (int i = 0; i < 10; i++) {
    fprintf(f, "// The count numbers is %d\n", i + 1);
  }

  fclose(f);

  if ((f = fopen("./data.txt", "r+")) == NULL) {
    printf("Cannot open the file...");
    exit(1);
  }

  printf("File content is--\n");
  printf("\n...print the strings...\n\n");

  while (fgets(ch, 100, f)) {
    printf("%s", ch);
  }

  fclose(f);

  return 0;
}
