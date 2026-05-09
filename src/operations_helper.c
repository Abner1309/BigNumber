#include <stdlib.h>
#include "operations_helper.h"
#include "utilities.h"

Number* memory_allocation_number(const Operation* operation) {
    // MEMORY ALLOCATION - RESULT
    long int greater = 0;
    Number* result = (Number*) malloc(sizeof(Number));
    memory_verification(result);

    // DETERMINE CAPACITY
    if (operation->number1->elements > operation->number2->elements) { greater = operation->number1->elements + 1; }
    else { greater = operation->number2->elements + 1; }

    // MEMORY ALLOCATION - RESULT DIGITS
    result->digits = (char*) malloc(greater * sizeof(char));
    memory_verification(result->digits);
    result->capacity = greater;
    result->elements = 0;
    result->signal = operation->number1->signal;

    // FILL DIGITS WITH ZEROS
    for (int i = 0; i < greater; i++) {
        result->digits[i] = '0';
    }

    return result;
}
