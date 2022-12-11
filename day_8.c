#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LINE_SIZE 200

bool visible(int tree_idx, int *trees, int stride, int length) {
    bool visible = true;

    // Row
    int row_begin = (tree_idx / stride) * stride;
    for (size_t i = row_begin; i < row_begin + stride; i++) {
        // Check and reset before computing from the other direction.
        if (i == tree_idx) {
            if (visible) return visible;  // left
            visible = true;
            continue;
        }

        if (trees[i] >= trees[tree_idx]) visible = false;
    }

    if (visible) return visible;  // right

    visible = true;  // reset

    // Column
    int col_offset = tree_idx - row_begin;
    for (size_t row_offset = 0; row_offset < stride * length; row_offset += stride) {
        // Check and reset before computing from the other direction.
        if (row_offset + col_offset == tree_idx) {
            if (visible) return visible; // top
            visible = true;
            continue;
        }

        if (trees[row_offset + col_offset] >= trees[tree_idx]) visible = false;
    }

    return visible; // bottom
}

int scenic_score(int tree_idx, int *trees, int stride, int length) {
    int score = 1;

    // Row
    int left_blocked_idx = -1, right_blocked_idx = -1;
    int row_begin = (tree_idx / stride) * stride;
    for (size_t i = row_begin; i < row_begin + stride; i++) {
        if (i < tree_idx) {
            // visibility from left
            if (trees[i] >= trees[tree_idx]) left_blocked_idx = i;
        } else if (i > tree_idx) {
            // visibility from right
            if (trees[i] >= trees[tree_idx]) {
                right_blocked_idx = i;
                break;
            }
        }
    }

    if (left_blocked_idx == -1) {
        score *= tree_idx - row_begin;
    } else {
        score *= tree_idx - left_blocked_idx;
    }

    if (right_blocked_idx == -1) {
        score *= row_begin + stride - tree_idx;
    } else {
        score *= right_blocked_idx - tree_idx;
    }

    // Column
    int top_blocked_idx = -1, bottom_blocked_idx = -1;
    int col_offset = tree_idx - row_begin;
    for (size_t row_offset = 0; row_offset < stride * length; row_offset += stride) {
        if (row_offset + col_offset < tree_idx) {
            // visibility from top
            if (trees[row_offset + col_offset] >= trees[tree_idx]) {
                top_blocked_idx = row_offset + col_offset;
            }
        } else if (row_offset + col_offset > tree_idx) {
            // visibility from bottom
            if (trees[row_offset + col_offset] >= trees[tree_idx]) {
                bottom_blocked_idx = row_offset + col_offset;
                break;
            }
        }
    }

    if (top_blocked_idx == -1) {
        score *= tree_idx / stride;
    } else {
        score *= (tree_idx - top_blocked_idx) / stride;
    }

    if (bottom_blocked_idx == -1) {
        score *= (stride*length-tree_idx) / stride;
    } else {
        score *= (bottom_blocked_idx - tree_idx) / stride;
    }

    return score;
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        exit(1);
    }

    int length = 0, stride = 0;

    char buf[LINE_SIZE];
    FILE* input = fopen(argv[1], "r");
    while (fgets(buf, LINE_SIZE, input) != NULL) {
        buf[strcspn(buf, "\n")] = 0;  // strip trailing newline
        length++;
    }
    stride = strlen(buf);
    rewind(input);

    int *trees = malloc(stride * length * sizeof(int));
    int trees_idx = 0;

    while (fgets(buf, LINE_SIZE, input) != NULL) {
        buf[strcspn(buf, "\n")] = 0;  // strip trailing newline

        for (size_t i = 0; i < strlen(buf); i++)
            // https://stackoverflow.com/questions/628761/convert-a-character-digit-to-the-corresponding-integer-in-c
            trees[i + trees_idx] = buf[i] - '0';

        trees_idx += stride;
    }

    fclose(input);

    int visible_trees = stride * 2 + (length-2) * 2;
    int max_scenic_score = 0;

    for (size_t row = 1; row < length-1; row++) {
        for (size_t col = 1; col < stride-1; col++) {
            int idx = row*stride + col;
            bool is_visible = visible(idx, trees, stride, length);
            if (is_visible) visible_trees++;

            int score = scenic_score(idx, trees, stride, length);
            if (score > max_scenic_score) max_scenic_score = score;
        }
    };

    printf("Part 1: %d\n", visible_trees);
    printf("Part 2: %d\n", max_scenic_score);
}
