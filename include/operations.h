#ifndef BIGNUMBER_OPERATIONS_H
#define BIGNUMBER_OPERATIONS_H
#include "structure.h"

Number* operation_sum(const Operation* operation);
Number* operation_subtraction(const Operation* operation);
Number* operation_multiplication(const Operation* operation);
Number* operation_division(const Operation* operation);
Number* judge(const Operation* operation);

#endif //BIGNUMBER_OPERATIONS_H
