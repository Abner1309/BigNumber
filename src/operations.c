#include <stdlib.h>
#include "operations.h"
#include "receiving_data.h"
#include "utilities.h"

Number* operation_sum(const Operation* operation) {
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

    // SUM OPERATION
    long int a = operation->number1->elements - 1;
    long int b = operation->number2->elements - 1;
    long int c = greater - 1;
    int sum = 0;

    while (a > -1 && b > -1) {
        sum = (operation->number1->digits[a] - '0') + (operation->number2->digits[b] - '0') + (result->digits[c] - '0');
        result->digits[c] = (char) (sum % 10 + '0');
        result->digits[c - 1] = (char) (sum / 10 + '0');
        result->elements++;
        a--; b--; c--;
    }
    while (a > -1) {
        sum = (operation->number1->digits[a] - '0') + (result->digits[c] - '0');
        result->digits[c] = (char) (sum % 10 + '0');
        result->digits[c - 1] = (char) (sum / 10 + '0');
        result->elements++;
        a--; c--;
    }
    while (b > -1) {
        sum = (operation->number2->digits[b] - '0') + (result->digits[c] - '0');
        result->digits[c] = (char) (sum % 10);
        result->digits[c - 1] = (char) (sum / 10);
        result->elements++;
        b--; c--;
    }

    // LAST DIGIT VERIFICATION
    if (result->digits[0] != '0') { result->elements++; }

    return result;
}
