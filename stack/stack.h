#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdbool.h>

typedef struct StackEntry {
    void* value;
} StackEntry;

typedef struct Stack {
    int sp;
    int size;
    StackEntry *entries;
} Stack;

Stack new_stack(const int size) {
    Stack s = { .sp = -1, .size = size };
    s.entries = calloc(s.size, sizeof(StackEntry));
    return s;
}

void push_stack(Stack *s, void* val) {
    s->sp++;
    s->entries[s->sp].value = val;
}

void* pop_stack(Stack *s)  {
    void *ret = s->entries[s->sp].value;
    s->sp--;
    return ret;
}

void* peek_stack(Stack *s) {
    return s->entries[s->sp].value;
}

bool empty(Stack *s) {
    return s->sp == -1;
}

Stack reverse_stack(Stack *s) {
    Stack reversed = new_stack(s->size);
    while (!empty(s)) {
        push_stack(&reversed, pop_stack(s));
    }

    return reversed;
}

void free_stack(Stack *s) {
    for (size_t i = 0; i < s->entries; i++) {
        free(s->entries[i].value);
    }
}

#endif