#include <stdio.h>
#include <stdlib.h>
#include "readline/readline.h"

size_t newline(char ** line, size_t* length, FILE* file) {
    *line = readline("");
    if (*line == NULL) {
        return -1;
    }
    *length = strlen(*line);
    size_t return_param = *length;
    return return_param;
}