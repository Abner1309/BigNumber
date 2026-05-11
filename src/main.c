#include "operations.h"
#include "receiving_data.h"
#include "returning_data.h"

int main() {
    Operation* operation = extraction();
    Number* result = judge(operation);
    final_step(operation, result);
    return 0;
}