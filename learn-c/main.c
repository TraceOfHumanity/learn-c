#include <stdio.h>
#include <stdlib.h>

int main(void) {
    FILE *fp = fopen("./data.txt", "r");
    char buff[255];

    if (fp == NULL) {
        perror("fopen failed");
        return 1;
    }

    while (fscanf(fp, "%254s", buff) != EOF) {
        printf("%s ", buff);
    }

    fclose(fp);
    return 0;
}