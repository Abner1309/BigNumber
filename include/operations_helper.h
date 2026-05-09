#ifndef BIGNUMBER_OPERATIONS_HELPER_H
#define BIGNUMBER_OPERATIONS_HELPER_H
#include "structure.h"

Number* memory_allocation_number(const Operation* operation, long int capacity);
void subtraction_digit_correction(char indicator, const Number* number, int giver, int receiver);
void subtraction_helper(Number* number);

#endif //BIGNUMBER_OPERATIONS_HELPER_H
