#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LINE_SIZE 100

int main(int argc, char *argv[]) {
    if (argc < 2) {
        exit(1);
    }

    char buf[LINE_SIZE];
    FILE* input = fopen(argv[1], "r");
    while (fgets(buf, LINE_SIZE, input) != NULL) {
        buf[strcspn(buf, "\n")] = 0;  // strip trailing newline
    }
    fclose(input);
}
