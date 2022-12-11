#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "vendor/ht/ht.h"

#define LINE_SIZE 5

typedef struct Position {
    int x;
    int y;
} Position;

void serialise_position(Position p, char* out) {
    sprintf(out, "%d,%d", p.x, p.y);
}

void move_tail(Position head_prev, Position head, Position *tail, ht *tail_positions) {
    char head_pos[3], new_head_pos[3];
    serialise_position(head_prev, head_pos);
    serialise_position(head, new_head_pos);
    printf("head moving from %s to %s\n", head_pos, new_head_pos);

    // Record the new tail position.
    char *new_tail_pos = malloc(sizeof(char));
    serialise_position(*tail, new_tail_pos);

    ht_set(tail_positions, new_tail_pos, tail);
}

void next(Position *head, Position *tail, char direction, int steps, ht *tail_positions) {
    // Mutates head and tail.
    Position new_head = { 0, 0, }, new_tail = { 0, 0 };

    for (size_t i = 0; i < steps; i++) {
        switch (direction) {
            case 'U':
                new_head.y++;
                break;
            case 'R':
                new_head.x++;
                break;
            case 'D':
                new_head.y--;
                break;
            case 'L':
                new_head.x--;
                break;
        }
        move_tail(*head, new_head, tail, tail_positions);
        *head = new_head;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        exit(1);
    }

    Position head = { 0, 0 }, tail = { .0, .0 };
    ht *tail_positions = ht_create();

    char buf[LINE_SIZE];
    FILE* input = fopen(argv[1], "r");
    while (fgets(buf, LINE_SIZE, input) != NULL) {
        buf[strcspn(buf, "\n")] = 0;  // strip trailing newline

        char direction;
        int steps = 0;

        int i = 0;
        char *tok = strtok(buf, " ");
        while (tok != NULL) {
            if (i == 0) direction = *tok;
            if (i == 1) steps = atoi(tok);
            tok = strtok(NULL, " ");
            i++;
        }

        printf("  dir: %c steps: %d\n", direction, steps);

        next(&head, &tail, direction, steps, tail_positions);
    }

    printf("");
}
