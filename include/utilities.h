#ifndef BIGNUMBER_UTILITIES_H
#define BIGNUMBER_UTILITIES_H
#include "structure.h"

void memory_verification(const void* pointer);
void file_verification(const void* pointer);
void number_error();
void operator_error();
void print_error();
void print_number(const Number* number);
void division_by_zero_error();

#endif //BIGNUMBER_UTILITIES_H
