#include <stddef.h>
#include "operations.h"

#include <stdio.h>
#include <stdlib.h>

#include "operations_helper.h"
#include "utilities.h"

Number* operation_sum(const Operation* operation) {
    // DETERMINE CAPACITY
    const long int bigger = which_is_bigger(operation->number1, operation->number2);
    long int capacity = 0;

    if (bigger == 0 || bigger == 1) { capacity = operation->number1->elements + 1; }
    else { capacity = operation->number2->elements + 1; }

    // MEMORY ALLOCATION
    Number* result = memory_allocation_number(capacity);

    // SUM OPERATION
    long int a = operation->number1->elements - 1;
    long int b = operation->number2->elements - 1;
    long int c = result->capacity - 1;
    int sum = 0;
    while (a > -1 && b > -1) {
        sum = (operation->number1->digits[a] - '0') + (operation->number2->digits[b] - '0');
        result->digits[c] = (char) ((sum % 10 + '0') + (result->digits[c] - '0'));
        result->digits[c - 1] = (char) ((sum / 10 + '0') + (result->digits[c - 1] - '0'));
        a--; b--; c--;
    }
    while (a > -1) {
        sum = (operation->number1->digits[a] - '0');
        result->digits[c] = (char) ((sum % 10 + '0') + (result->digits[c] - '0'));
        result->digits[c - 1] = (char) ((sum / 10 + '0') + (result->digits[c - 1] - '0'));
        a--; c--;
    }
    while (b > -1) {
        sum = (operation->number2->digits[b] - '0');
        result->digits[c] = (char) ((sum % 10 + '0') + (result->digits[c] - '0'));
        result->digits[c - 1] = (char) ((sum / 10 + '0') + (result->digits[c - 1] - '0'));
        b--; c--;
    }

    // RESULT SIGNAL
    result->signal = operation->number1->signal;

    return result;
}

Number* operation_subtraction(const Operation* operation) {
    // DETERMINE CAPACITY
    const long int bigger = which_is_bigger(operation->number1, operation->number2);
    long int capacity = 0;

    if (bigger == 0 || bigger == 1) { capacity = operation->number1->elements; }
    else { capacity = operation->number2->elements; }

    // MEMORY ALLOCATION
    Number* result = memory_allocation_number(capacity);

    // SUBTRACTION OPERATION
    long int a = operation->number1->elements - 1;
    long int b = operation->number2->elements - 1;
    long int c = result->capacity - 1;
    int minus = 0;
    // SUBTRACTION OPERATION - BOTH NUMBERS ARE EQUAL
    if (bigger == 0) {
        return result;
    }
    // SUBTRACTION OPERATION - NUMBER ONE IS BIGGER
    else if (bigger == 1) {
        result->signal = operation->number1->signal;
        while (a > -1 && b > -1) {
            minus = (operation->number1->digits[a] - '0') - (operation->number2->digits[b] - '0');
            if (minus < 0) {
                subtraction_loan(operation->number1, subtraction_find_giver(operation->number1, a), a);
                minus = (operation->number1->digits[a] - '0') - (operation->number2->digits[b] - '0');
            }
            result->digits[c] = (char) (minus + '0');
            a--; b--; c--;
        }
    }
    // SUBTRACTION OPERATION - NUMBER TWO IS BIGGER
    else {
        result->signal = operation->number2->signal;
        while (a > -1 && b > -1) {
            minus = (operation->number2->digits[b] - '0') - (operation->number1->digits[a] - '0');
            if (minus < 0) {
                subtraction_loan(operation->number2, subtraction_find_giver(operation->number2, b), b);
                minus = (operation->number2->digits[b] - '0') - (operation->number1->digits[a] - '0');
            }
            result->digits[c] = (char) (minus + '0');
            a--; b--; c--;
        }
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
    while (this_division_is_possible(division_rest, operation->number2) != 2) {
        digit_value = division_ten_digit(division_rest, operation->number2);
        Number* aux = create_division_number(operation->number2, digit_value);
        while (this_division_is_possible(division_rest, aux) != 2) {

            printf("DIVISION REST: ");
            print_number(division_rest);
            printf("Capacity: %ld\n", division_rest->capacity);
            printf("Elements: %ld\n\n", division_rest->elements);

            printf("AUXILIARY: ");
            print_number(aux);
            printf("Capacity: %ld\n", aux->capacity);
            printf("Elements: %ld\n\n", aux->elements);

            Number* temp = subtraction_for_division(division_rest, aux);

            printf("TEMPORARY: ");
            print_number(temp);
            printf("Capacity: %ld\n", temp->capacity);
            printf("Elements: %ld\n", temp->elements);
            printf("==========================================================================\n");

            result->digits[result->capacity - digit_value - 1]++;
            free_number(division_rest);
            division_rest = temp;
        }
        free_number(aux);
    }
    free_number(division_rest);

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
