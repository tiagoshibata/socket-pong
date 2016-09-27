#include <curses.h>
#include <stdio.h>

static WINDOW *win;
static int player_width;
static int terminal_width;
static int terminal_height;

void display_init() {
    win = initscr();
    cbreak();
    noecho();
    curs_set(0);
    getmaxyx(win, terminal_height, terminal_width);
}

void display_get_size(int *x, int *y) {
    *x = terminal_width;
    *y = terminal_height;
}

int display_set_size(int x, int y) {
    if (x > terminal_width || y > terminal_height) {
        fprintf(stderr, "Desired terminal dimensions %dx%d are too large.\n", x, y);
        return -1;
    }
    terminal_width = x;
    terminal_height = y;
    wresize(win, y, x);
    return 0;
}

void display_my_player(int x) {
    // Check terminal bounds
    int min_x = (player_width - 1) / 2, max_x = terminal_width + player_width / 2;
    x = x < min_x ? min_x : x;
    x = x > max_x ? max_x : x;
    mvhline(terminal_height - 1, x, 196, player_width);
}
