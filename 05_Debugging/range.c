#include "stdlib.h"
#include "stdio.h"


int main (int argc, char** argv) {
    int step = 1;
    int begin_number = 0;
    int end_number;
    if (argc == 1) {
        printf("HELP\n");
        return 0;
    }
    if (argc == 2) {
        end_number = atoi(argv[1]);
    }
    if (argc == 3) {
        end_number = atoi(argv[2]);
        begin_number = atoi(argv[1]);
    }
    if (argc == 4) {
        end_number = atoi(argv[2]);
        begin_number = atoi(argv[1]);
        step = atoi(argv[3]);
    }

    for (int range_iter = begin_number; range_iter < end_number; range_iter += step) {
        printf("%d\n", range_iter);
    }
}

