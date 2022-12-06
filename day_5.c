#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define STACK_SIZE 8

typedef struct Stack {
    int sp;
    char values[STACK_SIZE];
} Stack;

Stack new_stack() {
    Stack s = { .sp = -1 };
    return s;
}

void push_stack(Stack *s, char val) {
    s->sp++;
    s->values[s->sp] = val;
}

char pop_stack(Stack *s)  {
    char ret = s->values[s->sp];
    s->sp--;
    return ret;
}

void parse_stack_row(const char row[], Stack stacks[]) {
    for (size_t i = 0; i < strlen(row); i++) {
        if (row[i] >= 65 && row[i] <= 90) {
            // Reached a stack.
            // Stack index is one less than the label because the stacks are zero-indexed.
            push_stack(&stacks[i/4], row[i]);
        }
    }
}

void parse_move_row(const char row[]) {
    printf("len: %lu str: %s\n", strlen(row), row);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        exit(1);
    }

    bool finished_parsing_stack_rows = false;

    const int N_STACKS = 9;
    Stack stacks[N_STACKS];
    for (size_t i = 0; i < N_STACKS; i++) stacks[i] = new_stack();

    const int LINE_SIZE = 256;
    char buf[LINE_SIZE];
    FILE* input = fopen(argv[1], "r");
    while (fgets(buf, LINE_SIZE, input) != NULL) {
        buf[strcspn(buf, "\n")] = 0;  // strip trailing newline

        if (strlen(buf) > 1 && buf[1] == '1') {
            finished_parsing_stack_rows = true;
            continue;  // skip the stack labels
        }

        // parse
        if (!finished_parsing_stack_rows) {
            parse_stack_row(buf, stacks);
        } else if (strlen(buf) > 0 && buf[0] == 'm') {
            parse_move_row(buf);
        }
    }
    fclose(input);
}
