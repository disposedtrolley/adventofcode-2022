#include <stdio.h>
#include <stdlib.h>
#include "vendor/ht/ht.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        exit(1);
    }

    const int LINE_SIZE = 50;
    char buf[LINE_SIZE];
    FILE* input = fopen(argv[1], "r");
    while (fgets(buf, LINE_SIZE, input) != NULL) {
    }
    fclose(input);

    printf("Day 7\n");

    ht *my_hash = ht_create();
    printf("%p\n", my_hash);
}
