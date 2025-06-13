#include "main.h"
// non scrivete niente nel main.

int main() {
    initialize_ncurses();
    noecho();

    Menu menu = Menu();
    menu.start_menu();

    return 0;
}
