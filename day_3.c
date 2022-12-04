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

char common_2(const char comp1[], const char comp2[], const char comp3[]) {
    for (size_t i = 0; i < strlen(comp1); i++) {
        for (size_t j = 0; j < strlen(comp2); j++) {
            for (size_t k = 0; k < strlen(comp3); k++) {
                if (comp1[i] == comp2[j] && comp1[i] == comp3[k]) {
                    return comp1[i];
                }
            }
        }
    }

    return 0;
}

int part_1(const char fname[]) {
    int total_priorities = 0;

    const int LINE_SIZE = 60;
    char buf[LINE_SIZE];
    FILE* input = fopen(fname, "r");
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

    return total_priorities;
}

int part_2(const char fname[]) {
    int total_priorities = 0;

    const int LINE_SIZE = 60;
    FILE* input = fopen(fname, "r");

    int set_size = 0;
    char rucksacks[3][LINE_SIZE];

    while (fgets(rucksacks[set_size], LINE_SIZE, input) != NULL) {
        rucksacks[set_size][strcspn(rucksacks[set_size], "\n")] = 0;  // strip trailing newline

        if (set_size == 2) {
            total_priorities += priority(common_2(rucksacks[0], rucksacks[1], rucksacks[2]))
            set_size = 0;
        } else {
            set_size++;
        }
    }

    fclose(input);

    return total_priorities;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        exit(1);
    }

    printf("Part 1: %d\n", part_1(argv[1]));
    printf("Part 2: %d\n", part_2(argv[1]));
}
