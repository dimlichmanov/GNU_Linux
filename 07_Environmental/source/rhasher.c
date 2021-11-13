#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include "rhash.h" /* LibRHash interface */
#include <string.h>
#include "ctype.h"
#ifdef GET
#include "newline_get.h"
#endif
#ifdef READ
#include "newline_read.h"
#endif
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

    fprintf(stderr, "> ");
    while ((nread = newline(&line, &len, stdin)) != -1) {
        token = strtok(line, " ");
        int hash_mode = -1;
        if (strcasecmp(token, "MD5") == 0) {
            hash_mode = RHASH_MD5;
        }
        if (strcasecmp(token, "SHA1") == 0) {
            hash_mode = RHASH_SHA1;
        }
        if (strcasecmp(token, "TTH") == 0) {
            hash_mode = RHASH_TTH;
        }
        if (hash_mode == -1) {
            fprintf(stderr, "invalid nash mode\n> ");
            continue;
        }

        int hash_base;
        if (isupper(token[0])) {
            hash_base = RHPR_HEX | RHPR_UPPERCASE;
        } else {
            hash_base = RHPR_BASE32 | RHPR_UPPERCASE;
        }

        token = strtok(NULL, "\n");

        if (token[0] == '"') {
            int res = rhash_file(hash_mode, token+1, digest);
            if (res < 0) {
                fprintf(stderr, "LibRHash error: %s: %s\n> ", token+1, strerror(errno));
                continue;
            }
        } else {
            int res = rhash_msg(hash_mode, token, strlen(token), digest);
            if (res < 0) {
                fprintf(stderr, "message digest calculation error\n> ");
                continue;
            }
        }

        rhash_print_bytes(output, digest, rhash_get_digest_size(hash_mode), hash_base);

        printf("%s = %s\n", rhash_get_name(hash_mode), output);
        fprintf(stderr, "> ");
    }
    return 0;
}