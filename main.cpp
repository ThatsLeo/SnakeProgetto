#include "main.h"
#include "menu_handler/menu.cpp"

int main() {
    initialize_ncurses();

    int startx, starty, width, height;
    height = 10;
    width = 30;
    starty = (LINES - height) / 2; // Calculate for a center placement
    startx = (COLS - width) / 2;   // Calculate for a center placement
    WINDOW *menu_win = create_menu_window(height, width, starty, startx);

    const char *choices[] = {
        "Choice 1",
        "Choice 2",
        "Choice 3",
        "Choice 4",
        "Exit",
    };
    int n_choices = sizeof(choices) / sizeof(char *);

    int choice = handle_user_input(menu_win, choices, n_choices);

    mvprintw(0, 0, "You chose choice %d with choice string %s\n", choice, choices[choice - 1]);
    clrtoeol();
    refresh();
    getch();
    endwin();             // End ncurses
    return 0;
}