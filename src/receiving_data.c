#include <stdio.h>
#include <string.h>
#include "receiving_data.h"
#include "utilities.h"

void verify_first_digit(const Operation* operation, const int number, const char c) {
    if (c == '+') {
        if (number == 1) { operation->number1->signal = '+';}
        else if (number == 2) { operation->number2->signal = '+'; }
        else { print_error(); }
    }
    else if (c == '-') {
        if (number == 1) { operation->number1->signal = '-';}
        else if (number == 2) { operation->number2->signal = '-'; }
        else { print_error(); }
    }
    else if (c >= '0' && c <= '9') {
        if (number == 1) {
            operation->number1->digits[0] = c;
            operation->number1->elements++;
            operation->number1->signal = '+';
        }
        else if (number == 2) {
            operation->number2->digits[0] = c;
            operation->number2->elements++;
            operation->number2->signal = '+';
        }
        else { print_error(); }
    }
    else { print_error(); }
}

void determine_operator(Operation* operation) {
    if (operation->operator == '+') {
        if (operation->number1->signal == '+' && operation->number2->signal == '-' ||
            operation->number1->signal == '-' && operation->number2->signal == '+')
        { operation->operator = '-'; }
    }
    else if (operation->operator == '-') {
        if (operation->number1->signal == '+' && operation->number2->signal == '-' ||
            operation->number1->signal == '-' && operation->number2->signal == '+')
        { operation->operator = '+'; }
    }
}

Operation* extraction() {
    char input_file_path[512];

    // INPUT FILE
    printf("Enter the path to the input file: ");
    fgets(input_file_path, sizeof(input_file_path), stdin);
    input_file_path[strcspn(input_file_path, "\n")] = '\0';

    // OPEN FILE
    FILE* arq_input = fopen(input_file_path, "r");
    file_verification(arq_input);

    // CREATE POINTER FOR OPERATION
    Operation* operation = memory_allocation();

    // RECEIVE FIRST BIG NUMBER
    int c = 0;
    verify_first_digit(operation, 1, (char) fgetc(arq_input));
    while ((c = fgetc(arq_input)) != EOF && c != '\n' && c != ' ') {
        add_element(operation, 1, (char) c);
    }

    // RECEIVE SECOND BIG NUMBER
    verify_first_digit(operation, 2, (char) fgetc(arq_input));
    while ((c = fgetc(arq_input)) != EOF && c != '\n' && c != ' ') {
        add_element(operation, 2, (char) c);
    }

    // RECEIVE OPERATOR
    add_operator(operation, (char) fgetc(arq_input));

    // DETERMINE OPERATOR
    determine_operator(operation);

    return operation;
}
