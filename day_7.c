#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "stack/stack.h"
#include "vendor/ht/ht.h"

#define LINE_SIZE 100
#define DIRNAME_LENGTH 100
#define DEPTH 20

#define MAX_SIZE 100000

bool includes(const char *str, const char *substr) {
    return strstr(str, substr) != NULL;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        exit(1);
    }

    ht *dirs = ht_create();
    Stack path = stack_new(DEPTH);

    char buf[LINE_SIZE];
    FILE* input = fopen(argv[1], "r");
    while (fgets(buf, LINE_SIZE, input) != NULL) {
        buf[strcspn(buf, "\n")] = 0;  // strip trailing newline
        if (strlen(buf) == 0) continue;

        if (buf[0] == '$' && buf[2] == 'c') {  // cd
            char *tok;
            char *command = buf;
            int i = 0;
            while ((tok = strtok_r(command, " ", &command)))
                if (++i == 3) break;

            char *val = malloc(sizeof(char));
            strcpy(val, tok);
            if (strcmp(val, "/") == 0) val = "ROOT";

            if (strcmp(val, "..") == 0) {
                stack_pop(&path);
            } else {
                stack_push(&path, val);

                char joined[DIRNAME_LENGTH * DEPTH] = {0};
                stack_join(&path, "/", joined);
                ht_set(dirs, joined, 0);
            }
        } else if (isdigit(buf[0])) {  // file listing
            char *tok;
            char *fsize = buf;
            int i = 0;
            while ((tok = strtok_r(fsize, " ", &fsize)))
                if (++i == 1) break;

            char *val = malloc(sizeof(char));
            strcpy(val, tok);

            char joined[DIRNAME_LENGTH * DEPTH] = {0};
            stack_join(&path, "/", joined);
            int curr_size = ht_get(dirs, joined);
            ht_set(dirs, joined, curr_size + atoi(val));
        }
    }
    fclose(input);

    int sum_sizes = 0;

    hti iterator = ht_iterator(dirs);
    while (ht_next(&iterator)) {
        int total_size = iterator.value;

        hti jiterator = ht_iterator(dirs);
        while (ht_next(&jiterator)) {
            if (!includes(jiterator.key, iterator.key) || strcmp(iterator.key, jiterator.key) == 0) continue;
            total_size += jiterator.value;
        }

        if (total_size <= MAX_SIZE) sum_sizes += total_size;
    }

    stack_free(&path);
    ht_destroy(dirs);

    printf("Part 1: %d\n", sum_sizes);
}
