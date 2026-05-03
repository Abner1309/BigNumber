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

void free_resources(Operation* operation) {
    free(operation->number2->digits);
    free(operation->number2);
    free(operation->number1->digits);
    free(operation->number1);
    free(operation);
}
