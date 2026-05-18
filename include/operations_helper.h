#ifndef BIGNUMBER_OPERATIONS_HELPER_H
#define BIGNUMBER_OPERATIONS_HELPER_H
#include "structure.h"

Number* memory_allocation_number(long int capacity);
Number* copy_number(const Number* number);
Number* create_division_number(const Number* number, int ten);
void subtraction_loan(char indicator, const Number* number, int giver, int receiver);
void subtraction_adjustment_digit(const Number* number);
void subtraction_helper(Number* number);
void multiplication_division_signal(const Operation* operation, Number* number);
int which_is_bigger(const Number* n1, const Number* n2);

#endif //BIGNUMBER_OPERATIONS_HELPER_H
