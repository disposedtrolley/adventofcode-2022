#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

void parse_stack_row(const char row[]) {
    printf("len: %lu str: %s\n", strlen(row), row);
}

void parse_move_row(const char row[]) {
    printf("len: %lu str: %s\n", strlen(row), row);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        exit(1);
    }

    bool finished_parsing_stack_rows = false;

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
            parse_stack_row(buf);
        } else if (strlen(buf) > 0 && buf[0] == 'm') {
            parse_move_row(buf);
        }
    }
    fclose(input);
}
