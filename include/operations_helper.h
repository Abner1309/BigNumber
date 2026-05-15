#ifndef BIGNUMBER_OPERATIONS_HELPER_H
#define BIGNUMBER_OPERATIONS_HELPER_H
#include "structure.h"

Number* memory_allocation_number(const Operation* operation, long int capacity);
void subtraction_loan(char indicator, const Number* number, int giver, int receiver);
void subtraction_adjustment_digit(const Number* number);
void subtraction_helper(Number* number);
void multiplication_division_signal(const Operation* operation, Number* number);
int which_is_bigger(Number* n1, Number* n2);

#endif //BIGNUMBER_OPERATIONS_HELPER_H
