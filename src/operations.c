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
    Number* result = memory_allocation_number(capacity);

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
    Number* result = memory_allocation_number(capacity);

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

Number* operation_subtraction2(const Number* n1, const Number* n2) {
    // DETERMINE CAPACITY
    long int capacity;
    if (n1->elements > n2->elements) { capacity = n1->elements; }
    else { capacity = n2->elements; }

    // MEMORY ALLOCATION
    Number* result = memory_allocation_number(capacity);

    // SUBTRACTION OPERATION - PART I
    long int a = n1->elements - 1;
    long int b = n2->elements - 1;
    long int c = result->capacity - 1;
    int minus = 0;
    while (a > -1 && b > -1) {
        minus = (n1->digits[a] - '0') - (n2->digits[b] - '0');
        result->digits[c] = (char) (minus + '0');
        a--; b--; c--;
    }
    while (a > -1) {
        minus = (n1->digits[a] - '0');
        result->digits[c] = (char) (minus + '0');
        a--; c--;
    }
    while (b > -1) {
        minus = (n2->digits[b] - '0');
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
    Number* result = memory_allocation_number(capacity);

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
    if (which_is_bigger(operation->number1, operation->number2) == 1) {
        max_capacity = operation->number1->elements - operation->number2->elements + 1;
    }
    else if (which_is_bigger(operation->number1, operation->number2) == 2) {
        Number* number = memory_allocation_number(1);
        return number;
    }
    else {
        Number* number = memory_allocation_number(1);
        number->digits[number->elements - 1] = '1';
        return number;
    }

    // DIVISION BY ZERO
    if (operation->number2->elements == 1 && operation->number2->digits[0] == '0') {
        division_by_zero_error();
    }

    // DIVISION BY ONE
    if (operation->number2->elements == 1 && operation->number2->digits[0] == '1') {
        Number* number = memory_allocation_number(max_capacity);
        for (int i = 0; i < max_capacity; i++) {
            number->digits[i] = operation->number1->digits[i];
        }
        return number;
    }

    // MEMORY ALLOCATION
    Number* result = memory_allocation_number(max_capacity);

    // CREATE REST OF THE DIVISION
    Number* division_rest = copy_number(operation->number1);

    // DIVISION OPERATION
    long int digit_value = 0;
    while (which_is_bigger(division_rest, operation->number2) != 2) {
        digit_value = division_ten_digit(division_rest, operation->number2);
        Number* aux = create_division_number(operation->number2, digit_value);
        while (which_is_bigger(division_rest, aux) != 2) {
            Number* temp = operation_subtraction2(division_rest, aux);
            result->digits[result->capacity - digit_value - 1]++;
            free_number(division_rest);
            division_rest = temp;
        }
        free_number(aux);
    }

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
