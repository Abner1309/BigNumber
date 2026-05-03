#include <stdlib.h>
#include "structure.h"
#include "utilities.h"

Operation* memory_allocation() {
    Operation* operation = (Operation*) malloc(sizeof(Operation));
    memory_verification(operation);

    operation->number1 = (Number*) malloc(sizeof(Number));
    memory_verification(operation->number1);

    operation->number1->digits = (char*) malloc(10 * sizeof(char));
    memory_verification(operation->number1->digits);

    operation->number2 = (Number*) malloc(sizeof(Number));
    memory_verification(operation->number2);

    operation->number2->digits = (char*) malloc(10 * sizeof(char));
    memory_verification(operation->number2->digits);

    return operation;
}

void memory_reallocation(const Operation* operation, const int number) {
    if (number == 1) {
        const long int new_capacity = 2 * operation->number1->capacity;
        char* temp = (char*) realloc(operation->number1->digits, new_capacity * sizeof(char));
        memory_verification(temp);
        operation->number1->digits = temp;
        operation->number1->capacity = new_capacity;
    }
    else if (number == 2) {
        const long int new_capacity = 2 * operation->number2->capacity;
        char* temp = (char*) realloc(operation->number2->digits, new_capacity * sizeof(char));
        memory_verification(temp);
        operation->number2->digits = temp;
        operation->number2->capacity = new_capacity;
    }
    else {
        print_error();
    }
}

void free_resources(Operation* operation) {
    free(operation->number2->digits);
    free(operation->number2);
    free(operation->number1->digits);
    free(operation->number1);
    free(operation);
}
