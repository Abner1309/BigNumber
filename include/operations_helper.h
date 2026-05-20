#ifndef BIGNUMBER_OPERATIONS_HELPER_H
#define BIGNUMBER_OPERATIONS_HELPER_H
#include "structure.h"

Number* memory_allocation_number(long int capacity);
Number* copy_number(const Number* number);
Number* create_division_number(const Number* number, long int ten);
long int subtraction_find_giver(const Number* number, long int receiver);
void subtraction_loan(const Number* number, long int giver, long int receiver);
void multiplication_division_signal(const Operation* operation, Number* number);
int which_is_bigger(const Number* n1, const Number* n2);
int this_division_is_possible(const Number* n1, const Number* n2);
Number* subtraction_for_division(const Number* n1, const Number* n2);

#endif //BIGNUMBER_OPERATIONS_HELPER_H
