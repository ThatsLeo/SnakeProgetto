#include "main.h"

int main() {
    initscr();            // Initialize ncurses
    printw("Hello, Gays!");
    refresh();            // Refresh the screen
    getch();              // Wait for a key press
    endwin();             // End ncurses
    return 0;
}
