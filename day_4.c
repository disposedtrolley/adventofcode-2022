#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int fully_contains(const int r1[], const int r2[]) {
    return r2[0] >= r1[0] && r2[1] <= r1[1] || r1[0] >= r2[0] && r2[1] >= r1[1];
}

int contains(const int r1[], const int r2[]) {
    // r1 = [5, 7]
    // r2 = [7, 9]

    // r1 = [6, 6]
    // r2 = [4, 6]

    // r1 = [2, 6]
    // r2 = [3, 3]
    return r1[1] >= r2[0] && r1[1] <= r2[1] || r1[0] >= r2[0] && r1[0] <= r2[1] || \
        r2[0] >= r1[0] && r2[0] <= r1[1];
}

int compute_contains(char fname[], int(*contains_func)(const int r1[], const int r2[])) {
    int total = 0;

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

        total += contains_func(ranges[0], ranges[1]);
    }
    fclose(input);

    return total;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        exit(1);
    }

    printf("Part 1: %d\n", compute_contains(argv[1], fully_contains));
    printf("Part 2: %d\n", compute_contains(argv[1], contains));
}
