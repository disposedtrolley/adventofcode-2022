#include <stdio.h>
#include <stdlib.h>

int score_from_results(int opponent, int me) {
    int result = opponent - me;
    int score = 0;
    // ASCII :D
    if (result == -23) score += 3;
    if (result == -24) score += 6;
    if (result == -21) score += 6;
//        if (result == -25) score += 0;
//        if (result == -22) score += 0;
    return score + me - 87;  // Add points for the shape used (rock, paper, or scissors).
}

int part_2(const char filename[]) {
    int total_score = 0;

    const int LINE_SIZE = 5;
    char buf[LINE_SIZE];

    FILE* input = fopen(filename, "r");
    while (fgets(buf, LINE_SIZE, input) != NULL) {
        int opponent = buf[0];
        char outcome = buf[2];
        int me = 0;  // emulates the second column values from Part 1.
        switch(outcome) {
            case 'X': // 88
                if (opponent == 'A') me = 'Z';
                if (opponent == 'B') me = 'X';
                if (opponent == 'C') me = 'Y';
                break;
            case 'Y': // 89
                me = opponent + 23;  // choose the same shape as the opponent.
                break;
            case 'Z': // 90
                if (opponent == 'A') me = 'Y';
                if (opponent == 'B') me = 'Z';
                if (opponent == 'C') me = 'X';
                break;
        }

        total_score += score_from_results(opponent, me);
    }
    fclose(input);

    return total_score;
}

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
        total_score += score_from_results(opponent, me);
    }
    fclose(input);

    printf("Part 1: %d\n", total_score);
    printf("Part 2: %d\n", part_2(argv[1]));
}
