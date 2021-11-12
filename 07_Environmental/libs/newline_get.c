#include <stdio.h>
#include <stdlib.h>

size_t newline(char ** line, size_t* length, FILE* file) {
    size_t nread = getline(line, length, file);
    return nread;
}