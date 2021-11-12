#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "rhash.h" /* LibRHash interface */
#include <string.h>


//Using some copy-paste from rhash documentation code

int main(int argc, char *argv[]) {
    const char *filepath = "test_file.txt";
    unsigned char digest[64];
    char output[130];
    char *token = NULL;
    size_t len = 0;
    FILE *stream;
    char *line = NULL;
    __ssize_t nread;

    rhash_library_init(); /* initialize static data */

    while ((nread = getline(&line, &len, stdin)) != -1) {
        token = strtok(line, " ");
        if (strcasecmp(token, "MD5") == 0) {
            int res = rhash_msg(RHASH_MD5, line, strlen(line), digest);
            if (res < 0) {
                fprintf(stderr, "message digest calculation error\n");
                return 1;
            }
        }
//        int res = rhash_file(RHASH_TTH, filepath, digest);
//        if (res < 0) {
//            fprintf(stderr, "LibRHash error: %s: %s\n", filepath, strerror(errno));
//            return 1;
//        }

//        /* convert binary digest to hexadecimal string */
//        rhash_print_bytes(output, digest, rhash_get_digest_size(RHASH_MD4),
//                          (RHPR_BASE32 | RHPR_UPPERCASE));

        rhash_print_bytes(output, digest, rhash_get_digest_size(RHASH_MD5),
                          (RHPR_HEX | RHPR_UPPERCASE));


        printf("%s = %s\n", rhash_get_name(RHASH_MD5), output);
//        printf("%s (%s) = %s\n", rhash_get_name(RHASH_TTH), filepath, output);

    }
    return 0;
}