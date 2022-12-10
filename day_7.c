#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "stack/stack.h"
#include "vendor/ht/ht.h"

#define LINE_SIZE 100
#define DIRNAME_LENGTH 100

void parse_cd(char command[LINE_SIZE], char **curr_dir) {
    char dest_dir[DIRNAME_LENGTH];

    char *tok;
    char *rest = command;

    int i = 0;
    while ((tok = strtok_r(rest, " ", &rest))) {
        if (i < 2) {
            i++;
            continue;
        }

        strcpy(dest_dir, tok);
    }

    // We can either traverse up a directory or down.

    strcpy(*curr_dir, dest_dir);
}

void parse_command(char command[LINE_SIZE], char **curr_dir) {
    printf("addr inside: %p\n", curr_dir);
    if (strlen(command) < 4) {
        printf("malformed command string: %s\n", command);
        exit(1);
    }

    switch (command[2]) {
        case 'c':  // cd
            parse_cd(command, curr_dir);
            break;
        case 'l':  // ls
            break;
    }

    printf("new dir outside: %s\n", *curr_dir);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        exit(1);
    }

    char *curr_dir = NULL;
    curr_dir = malloc(sizeof(char) * DIRNAME_LENGTH);

    char buf[LINE_SIZE];
    FILE* input = fopen(argv[1], "r");
    while (fgets(buf, LINE_SIZE, input) != NULL) {
        buf[strcspn(buf, "\n")] = 0;  // strip trailing newline

        if (strlen(buf) > 0 && buf[0] == '$') parse_command(buf, &curr_dir);
    }
    fclose(input);

    printf("curr_dir is: %s\n", curr_dir);
}
