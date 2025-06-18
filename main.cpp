#include "main.h"

int main() {
    initialize_ncurses();
    noecho();

    Menu menu = Menu();
    menu.start_menu();

    endwin();
    return 0;
}
