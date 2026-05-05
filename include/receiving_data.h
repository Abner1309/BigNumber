#ifndef BIGNUMBER_RECEIVING_DATA_H
#define BIGNUMBER_RECEIVING_DATA_H
#include "structure.h"

void verify_first_digit(const Operation* operation, int number, char c);
Operation* extraction();
void determine_operator(Operation* operation);

#endif //BIGNUMBER_RECEIVING_DATA_H
