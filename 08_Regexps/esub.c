#include "regex.h"
#include <stdio.h>
#include "string.h"
#include <ctype.h>
#include <stdlib.h>
#include "stdbool.h"
#define MAX_POCKET 20


void print_pocket(int begin, int end, char * string) {
    for (int i = begin; i < end; i++) {
        putc(string[i], stdout);
    }
}


int main(int argc, char **argv) {
    if (argc < 4) {
        puts("Wrong usage of esub tool");
    }

    char *regexp = argv[1], *substitution = argv[2], *string = argv[3];
    regex_t regex;

    int err = regcomp(&regex, regexp, REG_EXTENDED);
    if (err != 0){
        printf("error in regexp");
    }

    regmatch_t pm[MAX_POCKET];
    err = regexec(&regex, string, MAX_POCKET, pm, 0);
    if (err != 0){
        printf("error in exec");
    }

    for (int i = 0; i < pm[0].rm_so; i++) {
        putc(string[i], stdout);
    }

    bool esc_status = false;
    for (char *str = substitution; *str != '\0'; str++) {
        if (*str=='\\' && !esc_status) {
            esc_status = 1;
            continue;
        }
        if (isdigit(*str) && esc_status) {
            print_pocket(pm[atoi(str)].rm_so, pm[atoi(str)].rm_eo, string);
            esc_status = 0;
            continue;
        }
        if (*str=='\\' && esc_status) {
            putc(*str, stdout);
            esc_status = 0;
            continue;
        }
        if (esc_status) {
            switch (*str) {
                case '\'':
                    putc('\'', stdout);
                    continue;
                case '\"':
                    putc('\"', stdout);
                    continue;

                case 'a':
                    putc('\a', stdout);
                    continue;
                case 'b':
                    putc('\b', stdout);
                    continue;
                case 'e':
                    putc('\e', stdout);
                    continue;
                case 'f':
                    putc('\f', stdout);
                    continue;
                case 'n':
                    putc('\n', stdout);
                    continue;
                case 'r':
                    putc('\r', stdout);
                    continue;
                case 't':
                    putc('\t', stdout);
                    continue;
                case 'v':
                    putc('\v', stdout);
                    continue;

            }
        }
        putc(*str, stdout);
    }

    for (int i = pm[0].rm_eo; i < strlen(string); i++) {
        putc(string[i], stdout);
    }
    putc('\n',stdout);

    regfree(&regex);
    return 0;

}