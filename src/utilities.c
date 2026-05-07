#include <stdio.h>
#include <stdlib.h>
#include "utilities.h"

void memory_verification(const void* pointer) {
    if (pointer == NULL) {
        fprintf(stderr, "Error: Memory Allocation Error\n");
        exit(EXIT_FAILURE);
    }
}

void file_verification(const void* pointer) {
    if (pointer == NULL) {
        fprintf(stderr, "Error: The File Could Not Be Open\n");
        exit(EXIT_FAILURE);
    }
}

void number_error() {
    fprintf(stderr, "Error: The number must contain only digits [0, 9]\n");
    exit(EXIT_FAILURE);
}

void operator_error() {
    fprintf(stderr, "Error: The operator must contain one of these symbols: '+' or '-' or '*' or '/'.\n");
    exit(EXIT_FAILURE);
}

void print_error() {
    fprintf(stderr, "Error\n");
    exit(EXIT_FAILURE);
}

void print_number(const Number* number) {
    int i = 0;

    // PRINT SIGNAL
    printf("%c", number->signal);

    // IGNORE LEADING ZEROS
    while (number->digits[i] == '0') {
        i++;
    }

    // PRINT DIGITS
    const int j = i;
    while (i < number->elements + j) {
        printf("%c", number->digits[i]);
        i++;
    }

    // PRINT SPACE
    printf("\n");
}
