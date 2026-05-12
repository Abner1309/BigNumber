#include <string.h>
#include "returning_data.h"
#include "utilities.h"

void save_result(FILE* arq, const Number* number) {
    int i = 0;

    // IGNORE LEADING ZEROS
    while (i < number->capacity && number->digits[i] == '0') {
        i++;
    }

    // IF ALL DIGITS ARE ZEROS
    if (i == number->capacity) { fprintf(arq, "0"); }
    // IF THERE IS AT LEAST ONE DIGIT OTHER THAN ZERO
    else {
        // PRINT SIGNAL
        fprintf(arq, "%c", number->signal);
        // PRINT DIGITS
        while (i < number->capacity) {
            fprintf(arq, "%c", number->digits[i]);
            i++;
        }
    }

    // PRINT SPACE
    fprintf(arq, "\n");
}

void final_step(Operation* operation, Number* result) {
    char output_file_path[512];

    // OUTPUT FILE
    printf("Enter the path to the output file: ");
    fgets(output_file_path, sizeof(output_file_path), stdin);
    output_file_path[strcspn(output_file_path, "\n")] = '\0';

    // OPEN FILE
    FILE* arq_output = fopen(output_file_path, "w");
    file_verification(arq_output);

    // STORES RESULT
    save_result(arq_output, result);

    // FREE RESOURCES
    fclose(arq_output);
    free_resources(operation);
    free_number(result);
}
