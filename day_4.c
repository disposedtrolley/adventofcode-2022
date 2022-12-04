#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int fully_contains(const int r1[], const int r2[]) {
    return r2[0] >= r1[0] && r2[1] <= r1[1] || r1[0] >= r2[0] && r2[1] >= r1[1];
}

int part_1(char fname[]) {
    int total_fully_contains = 0;

    const int LINE_SIZE = 20;
    char buf[LINE_SIZE];
    FILE* input = fopen(fname, "r");
    while (fgets(buf, LINE_SIZE, input) != NULL) {
        buf[strcspn(buf, "\n")] = 0;  // strip trailing newline

        int ranges[2][2];
        size_t i = 0;

        char *assignment;
        char *assignment_pair = buf;
        while ((assignment = strtok_r(assignment_pair, ",", &assignment_pair))) {
            size_t j = 0;

            char *id;
            char *range = assignment;
            while ((id = strtok_r(range, "-", &range))) {
                ranges[i][j] = atoi(id);
                j++;
            }
            i++;
        }

        total_fully_contains += fully_contains(ranges[0], ranges[1]);
    }
    fclose(input);

    return total_fully_contains;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        exit(1);
    }

    printf("Part 1: %d\n", part_1(argv[1]));
}
