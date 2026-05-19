#include <stdlib.h>
#include "operations_helper.h"
#include "utilities.h"

Number* memory_allocation_number(const long int capacity) {
    // MEMORY ALLOCATION - RESULT
    Number* result = (Number*) malloc(sizeof(Number));
    memory_verification(result);

    // MEMORY ALLOCATION - RESULT DIGITS
    result->digits = (char*) malloc(capacity * sizeof(char));
    memory_verification(result->digits);
    result->capacity = capacity;
    result->elements = 0;

    // FILL DIGITS WITH ZEROS
    for (long int i = 0; i < capacity; i++) {
        result->digits[i] = '0';
        result->elements++;
    }

    return result;
}

Number* copy_number(const Number* number) {
    Number* new_number = (Number*) malloc(sizeof(Number));
    memory_verification(new_number);
    new_number->digits = (char*) malloc(number->elements * sizeof(char));
    memory_verification(new_number->digits);
    new_number->capacity = number->elements;
    new_number->elements = 0;
    new_number->signal = number->signal;

    for (long int i = 0; i < number->elements; i++) {
        new_number->digits[i] = number->digits[i];
        new_number->elements++;
    }

    return new_number;
}

Number* create_division_number(const Number* number, const long int ten) {
    long int i = 0;
    Number* division_number = (Number*) malloc(sizeof(Number));
    memory_verification(division_number);
    division_number->digits = (char*) malloc((number->elements + ten) * sizeof(char));
    memory_verification(division_number->digits);
    division_number->capacity = number->elements + ten;
    division_number->elements = 0;
    division_number->signal = number->signal;

    while (i < number->elements) {
        division_number->digits[i] = number->digits[i];
        division_number->elements++;
        i++;
    }
    while (i < number->elements + ten) {
        division_number->digits[i] = '0';
        division_number->elements++;
        i++;
    }

    return division_number;
}

long int subtraction_find_giver(const Number* number, long int receiver) {
    long int i = receiver - 1;
    while (i > -1) {
        if (number->digits[i] > '0') { return i; }
        i--;
    }
    return i;
}

void subtraction_loan(const Number* number, const long int giver, const long int receiver) {
    for (long int i = giver; i < receiver; i++) {
        number->digits[i]--;
        number->digits[i + 1] = (char) (number->digits[i + 1] + 10);
    }
}

void multiplication_division_signal(const Operation* operation, Number* number) {
    if ((operation->number1->signal == '+' && operation->number2->signal == '+') ||
        (operation->number1->signal == '-' && operation->number2->signal == '-')) {
        number->signal = '+';
    }
    else if ((operation->number1->signal == '+' && operation->number2->signal == '-') ||
             (operation->number1->signal == '-' && operation->number2->signal == '+')) {
        number->signal = '-';
    }
    else {
        print_error();
    }
}

int which_is_bigger(const Number* n1, const Number* n2) {
    if (n1->elements > n2->elements) { return 1; }
    if (n1->elements < n2->elements) { return 2; }
    for (long int i = 0; i < n1->capacity; i++) {
        if (n1->digits[i] > n2->digits[i]) { return 1; }
        if (n1->digits[i] < n2->digits[i]) { return 2; }
    }
    return 0;
}

int this_division_is_possible(const Number* n1, const Number* n2) {
    long int a = 0;
    long int b = 0;

    if (n1->elements > n2->elements) { return 1; }
    if (n1->elements < n2->elements) { return 2; }

    while (n1->digits[a] == '0' && a < n1->capacity) { a++; }
    while (n2->digits[b] == '0' && a < n2->capacity) { b++; }

    while (a < n1->capacity) {
        if (n1->digits[a] > n2->digits[b]) { return 1; }
        if (n1->digits[a] < n2->digits[b]) { return 2; }
        a++; b++;
    }

    return 0;
}

long int division_ten_digit(const Number* n1, const Number* n2) {
    long int difference = n1->elements - n2->elements;
    if (n1->digits[0] <= n2->digits[0]) { difference--; }
    return difference;
}

Number* subtraction_for_division(const Number* n1, const Number* n2) {
    // MEMORY ALLOCATION
    Number* result = memory_allocation_number(n1->capacity);

    // SUBTRACTION OPERATION
    long int a = n1->capacity - 1;
    long int b = n2->capacity - 1;
    long int c = result->capacity - 1;
    int minus = 0;
    result->signal = n1->signal;
    while (a > -1 && b > -1) {
        minus = (n1->digits[a] - '0') - (n2->digits[b] - '0');
        if (minus < 0) {
            subtraction_loan(n1, subtraction_find_giver(n1, a), a);
            minus = (n1->digits[a] - '0') - (n2->digits[b] - '0');
        }
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

    // ELEMENTS ADJUSTMENT
    long int i = 0;
    while (result->digits[i] == '0' && i < result->capacity) { i++; }
    result->elements = result->capacity - i;

    return result;
}
