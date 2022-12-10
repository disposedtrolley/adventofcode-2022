#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack/stack.h"
#include "vendor/ht/ht.h"

#define LINE_SIZE 100
#define DIRNAME_LENGTH 100
#define PATH_LENGTH 20

void parse_cd(char command[LINE_SIZE], Stack *path) {
    char *tok;
    int i = 0;
    while ((tok = strtok_r(command, " ", &command))) {
        if (++i == 3) break;
    }

    char *val = malloc(sizeof(char));
    strcpy(val, tok);

    if (strcmp(val, "..") == 0) {
        stack_pop(path);
    } else {
        stack_push(path, val);
    }

    printf("peek stack: %s\n", (char*)stack_peek(path));
}

void parse_command(char command[LINE_SIZE], Stack *path) {
    if (strlen(command) < 4) {
        printf("malformed command string: %s\n", command);
        exit(1);
    }

    switch (command[2]) {
        case 'c':  // cd
            parse_cd(command, path);
            break;
        case 'l':  // ls
            break;
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        exit(1);
    }

    Stack path = stack_new(PATH_LENGTH);

    char buf[LINE_SIZE];
    FILE* input = fopen(argv[1], "r");
    while (fgets(buf, LINE_SIZE, input) != NULL) {
        buf[strcspn(buf, "\n")] = 0;  // strip trailing newline

        if (strlen(buf) > 0 && buf[0] == '$') parse_command(buf, &path);
    }

    printf("top of path stack: %s\n", (char*)stack_peek(&path));
    fclose(input);

    stack_free(&path);
}
