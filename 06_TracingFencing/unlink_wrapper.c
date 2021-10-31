#define _GNU_SOURCE
#include <dlfcn.h>
#include <string.h>

typedef int (*type)(const char* filename);

int unlink(const char* filename) {
    if (strstr(filename, "PROTECT") != NULL) {
        return 0;
    }
    type unlink_system = (type)dlsym(RTLD_NEXT, "unlink");
    return unlink_system(filename);
}
