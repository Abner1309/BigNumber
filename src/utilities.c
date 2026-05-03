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

void print_error() {
    fprintf(stderr, "Error\n");
    exit(EXIT_FAILURE);
}
