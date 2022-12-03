#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int comp (const void* elem1, const void* elem2) {
    int f = *((int*)elem1);
    int s = *((int*)elem2);
    if (f > s) return -1;
    if (f < s) return 1;
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        exit(1);
    }

    int n_elves = 0;
    int* sums = malloc(sizeof(int));
    sums[0] = 0;

    const int LINE_SIZE = 6 + 1;
    char buf[LINE_SIZE];
    FILE* input = fopen(argv[1], "r");
    while (fgets(buf, LINE_SIZE, input) != NULL) {
        sums[n_elves] += atoi(buf);

        // Reset counter and allocate space for the next elf's calories.
        if (strcmp(buf, "\n") == 0) {
            n_elves += 1;
            sums = reallocarray(sums, n_elves+1, sizeof(int));
            sums[n_elves] = 0;
        }
    }
    fclose(input);

    qsort(sums, n_elves, sizeof(int), comp);

    printf("Part 1: %d\n", sums[0]);
    printf("Part 2: %d\n", sums[0] + sums[1] + sums[2]);
}
