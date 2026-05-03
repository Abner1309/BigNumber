#include <stdio.h>
#include <stdlib.h>
#include "utilities.h"

void memory_verification(const void* pointer) {
    if (pointer == NULL) {
        fprintf(stderr, "Error: Memory Allocation Error\n");
        exit(EXIT_FAILURE);
    }
}
