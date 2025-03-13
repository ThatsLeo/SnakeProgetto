#include "main.h"
#include "menu_handler/menu.cpp"

int main() {
    initialize_ncurses();

    start_menu();

    endwin();  
    
    return 0;
}