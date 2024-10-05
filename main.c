// By Eymard Alarcon //
#include <stdio.h>
#include <stdlib.h>
#include "forky.h"

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Usage: %s <number_of_things> <pattern_number>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int num_things = atoi(argv[1]);
    int pattern = atoi(argv[2]);

    if (num_things < 1 || num_things > 256) {
        fprintf(stderr, "Number of things must be between 1 and 256.\n");
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen("results.txt", "w");
    if (file == NULL) {
        perror("Unable to open results.txt");
        exit(EXIT_FAILURE);
    }

    switch (pattern) {
        case 1:
            fork_pattern_1(num_things, file);
            break;
        case 2:
            fork_pattern_2(num_things, file);
            break;
        default:
            fprintf(stderr, "Invalid pattern number. Must be 1, 2, or 3.\n");
            fclose(file);
            exit(EXIT_FAILURE);
    }

    fclose(file);
    return 0;
}
