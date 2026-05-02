#include <stdio.h>
#include <stdlib.h>
#include "structure.h"

Operation* memory_allocation() {
    Operation* new_operation = (Operation*) malloc(sizeof(Operation));
    if (new_operation == NULL) {
        fprintf(stderr, "Error: Memory Allocation Error\n");
        exit(EXIT_FAILURE);
    }

    new_operation->number_a = (char*) malloc(10 * sizeof(char));
    if (new_operation->number_a == NULL) {
        fprintf(stderr, "Error: Memory Allocation Error\n");
        exit(EXIT_FAILURE);
    }
    new_operation->capacity_a = 10;
    new_operation->elements_a = 0;

    new_operation->number_b = (char*) malloc(10 * sizeof(char));
    if (new_operation->number_b == NULL) {
        fprintf(stderr, "Error: Memory Allocation Error\n");
        exit(EXIT_FAILURE);
    }
    new_operation->capacity_b = 10;
    new_operation->elements_b = 0;

    return new_operation;
}

void free_resources(Operation* operation) {
    free(operation->number_b);
    free(operation->number_a);
    free(operation);
}
