#include "operations.h"
#include "operations_helper.h"

Number* operation_sum(const Operation* operation) {
    // MEMORY ALLOCATION
    Number* result = memory_allocation_number(operation);

    // SUM OPERATION
    long int a = operation->number1->elements - 1;
    long int b = operation->number2->elements - 1;
    long int c = result->capacity - 1;
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
