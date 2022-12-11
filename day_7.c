#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack/stack.h"
#include "vendor/ht/ht.h"

#define LINE_SIZE 100
#define DIRNAME_LENGTH 100
#define PATH_LENGTH 20

int main(int argc, char *argv[]) {
    if (argc < 2) {
        exit(1);
    }

    ht *dirs = ht_create();
    Stack path = stack_new(PATH_LENGTH);

    char buf[LINE_SIZE];
    FILE* input = fopen(argv[1], "r");
    while (fgets(buf, LINE_SIZE, input) != NULL) {
        buf[strcspn(buf, "\n")] = 0;  // strip trailing newline

        if (strlen(buf) > 0 && buf[0] == '$') {
            switch (buf[2]) {
                case 'c':  // cd
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

                        char joined[DIRNAME_LENGTH * 10] = {0};
                        stack_join(&path, "/", joined);
                        ht_set(dirs, joined, 0);
                    }
                    break;
                case 'l':  // ls
                    char joined[DIRNAME_LENGTH * 10] = {0};
                    stack_join(&path, "/", joined);

                    break;
            }
        }
    }
    fclose(input);

    printf("top of path stack: %s\n", (char*)stack_peek(&path));

    char joined[DIRNAME_LENGTH * 10];
    stack_join(&path, "/", joined);
    printf("joined: %s\n", joined);

    stack_free(&path);

    ht_destroy(dirs);
}
