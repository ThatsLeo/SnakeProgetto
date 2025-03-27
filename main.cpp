#include "main.h"
#include "menu_handler/main_menu.cpp"
#include "gioco/Livelli.cpp"

// non scrivete niente nel main.

// int main() {
//     initialize_ncurses();
//     Menu menu = Menu();

//     menu.start_menu();

//     return 0;
// }
int main() {
    initialize_ncurses();
    clear();
    refresh();
    WINDOW* box;
    box = newwin(2, 2, 0, 0);
    wrefresh(box);
    wclear(box);
    Utils::CreateBoxWindowCentered(box, 2, 2);
    level *lvl = new level();
    lvl->PrintLevels();
    while (true) {
        refresh();
    }
    return 0;
}