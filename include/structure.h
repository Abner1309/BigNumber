#ifndef BIGNUMBER_STRUCTURE_H
#define BIGNUMBER_STRUCTURE_H

typedef struct {
    char* digits;
    long int capacity;
    long int elements;
    char signal;
} Number;

typedef struct {
    Number* number1;
    Number* number2;
    char operator;
} Operation;

Operation* memory_allocation();
void memory_reallocation(const Operation* operation, int number);
void add_element(const Operation* operation, int number, char c);
void add_operator(Operation* operation, char c);
void free_resources(Operation* operation);

#endif //BIGNUMBER_STRUCTURE_H
