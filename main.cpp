#include "main.h"
#include "menu_handler/main_menu.cpp"
#include "gioco/Livelli.cpp"

// non scrivete niente nel main.

int main() {
    initialize_ncurses();
    Menu menu = Menu();

    menu.start_menu();

    return 0;
}