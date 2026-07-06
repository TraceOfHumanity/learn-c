#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>

int main(void) {
  char *buffer = NULL;
  size_t bufferSize = 32;
  size_t characters;

  buffer = (char *)malloc(bufferSize * sizeof(char));

  if (buffer == NULL) {
    exit(1);
  }

  printf("type something: ");
  characters = getline(&buffer, &bufferSize, stdin);

  printf("%zu characters where read.\n", characters);

  return 0;
}
