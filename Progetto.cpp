#include <ncurses/ncurses.h>

int main() {
    initscr();            // Initialize ncurses
    printw("Hello, ncurses!");
    refresh();            // Refresh the screen
    getch();              // Wait for a key press
    endwin();             // End ncurses
    return 0;
}
