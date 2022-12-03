#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        exit(1);
    }

    int max_sum, curr_sum = 0;

    const int LINE_SIZE = 6 + 1;
    char buf[LINE_SIZE];
    FILE *input = fopen(argv[1], "r");
    while (fgets(buf, LINE_SIZE, input) != NULL) {
        // Reset counter for the next elf's calories.
        if (strcmp(buf, "\n") == 0) {
            if (curr_sum > max_sum) max_sum = curr_sum;
            curr_sum = 0;
        }

        curr_sum += atoi(buf);
    }
    fclose(input);

    printf("%d\n", max_sum);
}
