#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        exit(1);
    }

    int total_score = 0;

    const int LINE_SIZE = 5;
    char buf[LINE_SIZE];
    FILE* input = fopen(argv[1], "r");
    while (fgets(buf, LINE_SIZE, input) != NULL) {
        int opponent = buf[0];
        int me = buf[2];

        int result = opponent - me;
        int score = 0;
        if (result == -23) score += 3;
        if (result == -24) score += 6;
        if (result == -21) score += 6;
//        if (result == -25) score += 0;
//        if (result == -22) score += 0;
        score += me - 87;
        total_score += score;
    }
    fclose(input);

    printf("%d\n", total_score);
}
