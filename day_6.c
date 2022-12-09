#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        exit(1);
    }

    const int LINE_SIZE = 4096;
    char buf[4096];
    FILE* input = fopen(argv[1], "r");
    fgets(buf, LINE_SIZE, input);
    fclose(input);

    const int MARKER_LENGTH = 4;

    int marker_start = 0;
    for (size_t i = 0; i < LINE_SIZE; i++) {
        if (i >= LINE_SIZE - MARKER_LENGTH) break;

        bool has_duplicates = false;
        for (size_t j = i; j < i+MARKER_LENGTH; j++) {
            for (size_t k = j+1; k < j+MARKER_LENGTH; k++) {
                if (buf[j] == buf[k]) has_duplicates = true;
            }
        }

        if (!has_duplicates) {
            marker_start = i;
            break;
        }
    }

    printf("%d\n", marker_start+MARKER_LENGTH);
}
