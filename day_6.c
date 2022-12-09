#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void run(char fname[], int part) {
    const int LINE_SIZE = 4096;
    char buf[4096];
    FILE* input = fopen(fname, "r");
    fgets(buf, LINE_SIZE, input);
    fclose(input);

    int MARKER_LENGTH = 4;
    if (part == 2) MARKER_LENGTH = 14;

    int marker_start = 0;
    for (size_t i = 0; i < LINE_SIZE-MARKER_LENGTH; i++) {
        // Sliding window
        bool has_duplicates = false;
        for (size_t j = i; j < i+MARKER_LENGTH-1; j++) {
            for (size_t k = j+1; k < i+MARKER_LENGTH; k++) {
                if (buf[j] == buf[k] && j != k) {
                    has_duplicates = true;
                }
            }
        }

        if (!has_duplicates) {
            marker_start = i + MARKER_LENGTH;
            break;
        }
    }

    printf("Part %d: %d\n", part, marker_start);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        exit(1);
    }

    run(argv[1], 1);
    run(argv[1], 2);
}
