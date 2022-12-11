#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "stack/stack.h"
#include "vendor/ht/ht.h"

#define LINE_SIZE 100
#define DIRNAME_LENGTH 100
#define DEPTH 20

#define ROOT "ROOT"

#define MAX_SIZE 100000

#define FS_SPACE_AVAILABLE 70000000
#define FS_REQUIRED_FREE 30000000

bool includes(const char *str, const char *substr) {
    return strstr(str, substr) != NULL;
}

int comp (const void* elem1, const void* elem2) {
    int f = *((int*)elem1);
    int s = *((int*)elem2);
    if (f > s) return 1;
    if (f < s) return -1;
    return 0;
}

void part_1(ht *fs) {
    int sum_sizes = 0;

    hti iterator = ht_iterator(fs);
    while (ht_next(&iterator)) {
        int total_size = iterator.value;

        hti jiterator = ht_iterator(fs);
        while (ht_next(&jiterator)) {
            if (!includes(jiterator.key, iterator.key) || strcmp(iterator.key, jiterator.key) == 0) continue;
            total_size += jiterator.value;
        }

        if (total_size <= MAX_SIZE) sum_sizes += total_size;
    }

    printf("Part 1: %d\n", sum_sizes);
}

void part_2(ht *fs) {
    int used_space = 0;
    int *dir_sizes = NULL;

    int i = 0;
    hti iterator = ht_iterator(fs);
    while (ht_next(&iterator)) {
        int total_size = iterator.value;

        hti jiterator = ht_iterator(fs);
        while (ht_next(&jiterator)) {
            if (!includes(jiterator.key, iterator.key) || strcmp(iterator.key, jiterator.key) == 0) continue;
            total_size += jiterator.value;
        }

        dir_sizes = realloc(dir_sizes, (i+1) * sizeof(int));
        dir_sizes[i] = total_size;
        i++;

        if (strcmp(iterator.key, ROOT) == 0) used_space = total_size;
    }

    qsort(dir_sizes, i+1, sizeof(int), comp);

    for (size_t dir_idx = 0; dir_idx <= i; dir_idx++) {
        if (FS_SPACE_AVAILABLE - used_space + dir_sizes[dir_idx] >= FS_REQUIRED_FREE) {
            printf("Part 2: %d\n", dir_sizes[dir_idx]);
            break;
        }
    }
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
            if (strcmp(val, "/") == 0) val = ROOT;

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
    stack_free(&path);

    part_1(dirs);
    part_2(dirs);
    ht_destroy(dirs);
}
