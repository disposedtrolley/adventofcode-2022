#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdbool.h>

typedef struct StackEntry {
    void* value;
} StackEntry;

typedef struct Stack {
    int sp;
    int cap;
    int size;
    StackEntry *entries;
} Stack;

Stack stack_new(const int cap) {
    Stack s = { .sp = -1, .cap = cap, .size = 0 };
    s.entries = calloc(s.cap, sizeof(StackEntry));
    return s;
}

void stack_push(Stack *s, void* val) {
    s->sp++;
    s->size++;
    s->entries[s->sp].value = val;
}

void* stack_pop(Stack *s)  {
    void *ret = s->entries[s->sp].value;
    s->sp--;
    return ret;
}

void* stack_peek(Stack *s) {
    return s->entries[s->sp].value;
}

bool stack_empty(Stack *s) {
    return s->sp == -1;
}

Stack stack_reverse(Stack *s) {
    Stack reversed = stack_new(s->cap);
    while (!stack_empty(s)) {
        stack_push(&reversed, stack_pop(s));
    }

    return reversed;
}

void stack_free(Stack *s) {
    for (size_t i = 0; i < s->size; i++) {
        free(s->entries[i].value);
    }
}

#endif