// By Eymard Alarcon //
#include "forky.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <number_of_things> <pattern>\n", argv[0]);
        return 1;
    }

    int number_of_things = atoi(argv[1]);
    int pattern = atoi(argv[2]);

    if (number_of_things < 1 || number_of_things > 256) {
        fprintf(stderr, "Error: number_of_things must be between 1 and 256.\n");
        return 1;
    }

    if (pattern == 1) {
        fork_pattern_1(number_of_things);
    } else if (pattern == 2) {
        fork_pattern_2(number_of_things);
    } else {
        fprintf(stderr, "Error: pattern must be 1 or 2.\n");
        return 1;
    }

    return 0;
}
