#ifndef STACK_H
#define STACK_H

#include <stdbool.h>

#define STACK_SIZE 100

typedef struct Stack {
    int sp;
    void *values[STACK_SIZE];
} Stack;

Stack new_stack() {
    Stack s = { .sp = -1 };
    return s;
}

void push_stack(Stack *s, void* val) {
    s->sp++;
    s->values[s->sp] = val;
}

void* pop_stack(Stack *s)  {
    char ret = s->values[s->sp];
    s->sp--;
    return ret;
}

void* peek_stack(Stack *s) {
    return s->values[s->sp];
}

bool empty(Stack *s) {
    return s->sp == -1;
}

Stack reverse_stack(Stack *s) {
    Stack reversed = new_stack();
    while (!empty(s)) {
        push_stack(&reversed, pop_stack(s));
    }

    return reversed;
}

#endif