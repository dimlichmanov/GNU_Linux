#include "stdlib.h"
#include "stdio.h"
#include <errno.h>
#include "string.h"
#include <unistd.h>
#include <fcntl.h>

extern int errno ;
void safe_delete(char *filename) {
    unlink(filename);
}
#define READ_SIZE 100

int main(int argc, char** argv) {

    char* in_filename = argv[1];
    char* out_filename = argv[2];
    int in_fd, out_fd;
    int errnum;

    in_fd = open(in_filename, O_RDONLY);

    if (in_fd == -1) {
        errnum = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));
    }

    out_fd = open(out_filename, O_WRONLY|O_CREAT|O_TRUNC, 0666);

    if (out_fd == -1) {
        errnum = errno;
        fprintf(stderr, "Value of errno: %d\n", errno);
        perror("Error printed by perror");
        fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));
    }

    int read_bytes = 0;
    char* read_buffer = malloc(READ_SIZE);

    do {
        read_bytes = read(in_fd, read_buffer, READ_SIZE);
        if (read_bytes  == -1) {
            errnum = errno;
            fprintf(stderr, "Value of errno: %d\n", errno);
            perror("Error printed by perror");
            fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));
            close(in_fd);
            safe_delete(out_filename);
        }
        int write_bytes = write(out_fd, read_buffer, read_bytes);
        if (write_bytes != read_bytes) {
            errnum = errno;
            fprintf(stderr, "Value of errno: %d\n", errno);
            perror("Error printed by perror");
            fprintf(stderr, "Error opening file: %s\n", strerror( errnum ));
            close(in_fd);
            safe_delete(out_filename);
        }
    } while (read_bytes == READ_SIZE);

    close(in_fd);
    close(out_fd);

    safe_delete(in_filename);
    return 0;
}

