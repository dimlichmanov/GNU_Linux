#include "ncurses.h"
#include <sys/stat.h>
#include "stdlib.h"
#include "unistd.h"
#include "fcntl.h"
#include "string.h"
#include "locale.h"

#define margin 3

int main(int argc, char **argv) {
    WINDOW *display;
    int i, n, m, c = 0, fd, W, H, done, num_strings = 0;
    char *buf, *curr;
    char **strings;
    size_t len;

    /* Struct things are taken from GIF on a hometask page */
    struct stat info;
    stat(argv[1], &info);
    len = info.st_size;
    buf = malloc(len+2) + 1;
    buf[-1] = '\n';

    fd = open(argv[1], O_RDONLY);
    read(fd, buf, len);
    for (int i = 0; i < len + 1; i++) {
        if (buf[i] == '\n') {
            num_strings++;
        }
    }
    close(fd);

    strings = calloc(num_strings, sizeof(char*));
    strings[0] = buf;
    int j = 1;

    for (int i = 0; i < len + 1; i++) {
        if (buf[i] == '\n') {
            strings[j] = &buf[i] + 1;
            j++;
        }
    }

    for (int h = 0; h < num_strings; h++){
        int curr_size = strings[h + 1] - strings[h];
        char *sstr = (char*)malloc((curr_size + 1) * sizeof(char));
        sstr[curr_size] = '\0';
        memcpy(sstr, strings[h], curr_size);
        printf("%s", sstr);
        free(sstr);
    }

    setlocale(LC_ALL, "");

    initscr();
    noecho();
    cbreak();

    wrefresh(display);

    W = COLS - 2 * margin;
    H = LINES - 2 * margin;
    display = newwin(H, W, margin, margin);

    keypad(display, TRUE);
    scrollok(display, TRUE);
    n = 0; m = 0;
    done = FALSE;

    do {
        werase(display);
        for (i = 0; i < H-2 && i + n < num_strings; i++) {
            int curr_size = strings[i+ 1] - strings[i];
            char *sstr = (char*)malloc((curr_size + 1) * sizeof(char));
            sstr[curr_size] = '\0';
            memcpy(sstr, strings[i], curr_size);
            mvwprintw(display, i + 1, 1, "%s", sstr);
            free(sstr);
        }
        box(display, 0, 0);
        wrefresh(display);
        switch(c = wgetch(display)) {
            case 27:done = TRUE; break;
            case KEY_DOWN: n = n < num_strings - 1 ? n+1 : n; break;
            case KEY_UP: n = n > 0 ? n-1 : n; break;
            case KEY_RIGHT: m++; break;
            case KEY_LEFT: m = m > 0? m-1: 0; break;
        }
    } while (!done);

    endwin();
}