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
// int main() {
//     initialize_ncurses();
//     clear();
//     refresh();
//     initscr();
//     noecho();
//     cbreak();
//     int yMax, xMax;
//     getmaxyx(stdscr, yMax, xMax);
//     WINDOW *menuwin = newwin(30, xMax-10, yMax-30, 10);
//     box(menuwin, 0, 0);
//     refresh();
//     wrefresh(menuwin);
//     keypad(menuwin, TRUE);
//     while (true) {
//         mvwprintw(menuwin, 1, 1, "Press 'q' to quit or 'm' for menu");
//         refresh();
//         wrefresh(menuwin);
//     }
// }
