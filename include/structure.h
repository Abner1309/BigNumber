#ifndef BIGNUMBER_STRUCTURE_H
#define BIGNUMBER_STRUCTURE_H

typedef struct {
    char* number_a;
    long int capacity_a;
    long int elements_a;
    char* number_b;
    long int capacity_b;
    long int elements_b;
    char operator;
} Operation;

Operation* memory_allocation();
void free_resources(Operation* operation);

#endif //BIGNUMBER_STRUCTURE_H
