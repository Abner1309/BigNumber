#include <stdlib.h>
#include "operations_helper.h"
#include "utilities.h"

Number* memory_allocation_number(const Operation* operation, const long int capacity) {
    // MEMORY ALLOCATION - RESULT
    Number* result = (Number*) malloc(sizeof(Number));
    memory_verification(result);

    // MEMORY ALLOCATION - RESULT DIGITS
    result->digits = (char*) malloc(capacity * sizeof(char));
    memory_verification(result->digits);
    result->capacity = capacity;
    result->elements = 0;

    // FILL DIGITS WITH ZEROS
    for (int i = 0; i < capacity; i++) {
        result->digits[i] = '0';
        result->elements++;
    }

    return result;
}

void subtraction_loan(const char indicator, const Number* number, const int giver, const int receiver) {
    if (indicator == '+') {
        for (int i = giver; i < receiver; i++) {
            number->digits[i]--;
            number->digits[i + 1] = (char) (number->digits[i + 1] + 10);
        }
    }
    else if (indicator == '-') {
        for (int i = giver; i < receiver; i++) {
            number->digits[i]++;
            number->digits[i + 1] = (char) (number->digits[i + 1] - 10);
        }
    }
    else {
        print_error();
    }
}

void subtraction_adjustment_digit(const Number* number) {
    for (int i = 0, dif = 0; i < number->capacity; i++) {
        if (number->digits[i] < '0') {
            dif = ('0' - number->digits[i]) + '0';
            number->digits[i] = (char) dif;
        }
    }
}

void subtraction_helper(Number* number) {
    int first_number = 0;
    // FIND THE FIRST NUMBER THAT IS NOT ZERO
    while (number->digits[first_number] == '0') { first_number++; }
    // IF NOT EXISTS ANY DIGIT THAT IS DIFFERENT OF ZERO
    if (first_number == number->elements) { return; }
    // IF THE RESULT IS NEGATIVE
    if (number->digits[first_number] < '0') {
        number->signal = '-';
        for (int i = first_number, aux = first_number; i < number->elements; i++) {
            if (number->digits[i] < '0') { aux = i; }
            else if (number->digits[i] > '0') {
                subtraction_loan('-', number, aux, i);
            }
        }
    }
    // IF THE RESULT IS POSITIVE
    else {
        number->signal = '+';
        for (int i = first_number, aux = first_number; i < number->elements; i++) {
            if (number->digits[i] > '0') { aux = i; }
            else if (number->digits[i] < '0') {
                subtraction_loan('+', number, aux, i);
            }
        }
    }

    // FINAL ADJUSTMENT
    subtraction_adjustment_digit(number);
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
    for (int i = 0; i < n1->elements; i++) {
        if (n1->digits[i] > n2->digits[i]) { return 1; }
        if (n1->digits[i] < n2->digits[i]) { return 2; }
    }
    return 0;
}
