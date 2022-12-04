#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int priority(char c) {
    if (c <= 90) {  // uppercase
        return c - 38;
    } else if (c <= 122) { // lowercase
        return c - 96;
    }
}

char common(const char comp1[], const char comp2[]) {
    int len = strlen(comp1);
    if (len != strlen(comp2)) {
        printf("Compartments not equal length!\n");
        exit(1);
    }

    for (size_t i = 0; i < len; i++) {
        for (size_t j = 0; j < len; j++) {
            if (comp1[i] == comp2[j]) {
                return comp1[i];
            }
        }
    }

    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        exit(1);
    }

    int total_priorities = 0;

    const int LINE_SIZE = 60;
    char buf[LINE_SIZE];
    FILE* input = fopen(argv[1], "r");
    while (fgets(buf, LINE_SIZE, input) != NULL) {
        buf[strcspn(buf, "\n")] = 0;  // strip trailing newline
        int len = strlen(buf);
        int midway = len/2;
        if (len % 2 != 0) {
            printf("Rucksack '%s' doesn't have an even number of items (%d)!\n", buf, len);
            exit(1);
        }

        char compartment_1[midway+1], compartment_2[midway+1];

        for (size_t i = 0; i < midway; i++) compartment_1[i] = buf[i];
        compartment_1[midway] = 0;  // terminate string

        for (size_t i = 0; i < midway; i++) compartment_2[i] = buf[midway + i];
        compartment_2[midway] = 0;  // terminate string

        total_priorities += priority(common(compartment_1, compartment_2));
    }

    fclose(input);

    printf("Part 1: %d\n", total_priorities);
}
