#include <stddef.h>
#include "operations.h"
#include "operations_helper.h"
#include "utilities.h"

Number* operation_sum(const Operation* operation) {
    // DETERMINE CAPACITY
    long int capacity;
    if (operation->number1->elements > operation->number2->elements) { capacity = operation->number1->elements + 1; }
    else { capacity = operation->number2->elements + 1; }

    // MEMORY ALLOCATION
    Number* result = memory_allocation_number(operation, capacity);

    // SUM OPERATION
    long int a = operation->number1->elements - 1;
    long int b = operation->number2->elements - 1;
    long int c = result->capacity - 1;
    int sum = 0;
    while (a > -1 && b > -1) {
        sum = (operation->number1->digits[a] - '0') + (operation->number2->digits[b] - '0') + (result->digits[c] - '0');
        result->digits[c] = (char) (sum % 10 + '0');
        result->digits[c - 1] = (char) (sum / 10 + '0');
        a--; b--; c--;
    }
    while (a > -1) {
        sum = (operation->number1->digits[a] - '0') + (result->digits[c] - '0');
        result->digits[c] = (char) (sum % 10 + '0');
        result->digits[c - 1] = (char) (sum / 10 + '0');
        a--; c--;
    }
    while (b > -1) {
        sum = (operation->number2->digits[b] - '0') + (result->digits[c] - '0');
        result->digits[c] = (char) (sum % 10);
        result->digits[c - 1] = (char) (sum / 10);
        b--; c--;
    }

    // RESULT SIGNAL
    result->signal = operation->number1->signal;

    return result;
}

Number* operation_subtraction(const Operation* operation) {
    // DETERMINE CAPACITY
    long int capacity;
    if (operation->number1->elements > operation->number2->elements) { capacity = operation->number1->elements; }
    else { capacity = operation->number2->elements; }

    // MEMORY ALLOCATION
    Number* result = memory_allocation_number(operation, capacity);

    // SUBTRACTION OPERATION - PART I
    long int a = operation->number1->elements - 1;
    long int b = operation->number2->elements - 1;
    long int c = result->capacity - 1;
    int minus = 0;
    while (a > -1 && b > -1) {
        minus = (operation->number1->digits[a] - '0') - (operation->number2->digits[b] - '0');
        result->digits[c] = (char) (minus + '0');
        a--; b--; c--;
    }
    while (a > -1) {
        minus = (operation->number1->digits[a] - '0');
        result->digits[c] = (char) (minus + '0');
        a--; c--;
    }
    while (b > -1) {
        minus = (operation->number2->digits[b] - '0');
        result->digits[c] = (char) (minus + '0');
        b--; c--;
    }

    // SUBTRACTION OPERATION - PART II
    subtraction_helper(result);

    return result;
}

Number* operation_multiplication(const Operation* operation) {
    // DETERMINE CAPACITY
    const long int capacity = operation->number1->elements + operation->number2->elements;

    // MEMORY ALLOCATION
    Number* result = memory_allocation_number(operation, capacity);

    // MULTIPLICATION OPERATION
    int z = 1;
    long int a = operation->number1->elements - 1;
    long int b = operation->number2->elements - 1;
    long int c = result->capacity - z;
    int multiplication = 0;
    while (b > -1) {
        while (a > -1) {
            multiplication = (operation->number1->digits[a] - '0') * (operation->number2->digits[b] - '0');
            result->digits[c] = (char) ((multiplication % 10 + '0') + (result->digits[c] - '0'));
            result->digits[c - 1] = (char) ((multiplication / 10 + '0') + (result->digits[c - 1] - '0'));
            a--; c--;
        }
        a = operation->number1->elements - 1; b--; z++; c = result->capacity - z;
    }

    // DETERMINE SIGNAL
    multiplication_division_signal(operation, result);

    return result;
}

Number* operation_division(const Operation* operation) {
    // DETERMINE CAPACITY
    long int max_capacity = 0;
    if (operation->number1->elements >= operation->number2->elements) {
        max_capacity = operation->number1->elements - operation->number2->elements + 1;
    }
    else {
        Number* number = memory_allocation_number(operation, 1);
        return number;
    }

    // MEMORY ALLOCATION
    Number* result = memory_allocation_number(operation, max_capacity);

    // DIVISION OPERATION
    long int a = 0;
    long int b = 0;
    long int c = 0;

    // DETERMINE SIGNAL
    multiplication_division_signal(operation, result);

    return result;
}

Number* judge(const Operation* operation) {
    Number* result = NULL;
    if (operation->operator == '+') {
        result = operation_sum(operation);
    }
    else if (operation->operator == '-') {
        result = operation_subtraction(operation);
    }
    else if (operation->operator == '*') {
        result = operation_multiplication(operation);
    }
    else if (operation->operator == '/') {
        result = operation_division(operation);
    }
    else { operator_error(); }
    return result;
}
