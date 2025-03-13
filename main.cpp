#include "main.h"

void print_menu(WINDOW *menu_win, int highlight, const char *choices[], int n_choices) {
    int x, y, i;
    x = 2;
    y = 2;
    box(menu_win, 0, 0);
    for(i = 0; i < n_choices; ++i) {
        if(highlight == i + 1) { // Highlight the present choice
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", choices[i]);
            wattroff(menu_win, A_REVERSE);
        } else {
            mvwprintw(menu_win, y, x, "%s", choices[i]);
        }
        ++y;
    }
    wrefresh(menu_win);
}

int main() {
    initscr();            // Initialize ncurses
    clear();
    noecho();
    cbreak();             // Line buffering disabled. Pass on everything

    int startx, starty, width, height;
    height = 10;
    width = 30;
    starty = (LINES - height) / 2; // Calculate for a center placement
    startx = (COLS - width) / 2;   // Calculate for a center placement
    WINDOW *menu_win = newwin(height, width, starty, startx);
    keypad(menu_win, TRUE);
    const char *choices[] = {
        "Choice 1",
        "Choice 2",
        "Choice 3",
        "Choice 4",
        "Exit",
    };
    int n_choices = sizeof(choices) / sizeof(char *);
    int highlight = 1;
    int choice = 0;
    int c;

    print_menu(menu_win, highlight, choices, n_choices);
    while(1) {
        c = wgetch(menu_win);
        switch(c) {
            case KEY_UP:
                if(highlight == 1)
                    highlight = n_choices;
                else
                    --highlight;
                break;
            case KEY_DOWN:
                if(highlight == n_choices)
                    highlight = 1;
                else 
                    ++highlight;
                break;
            case 10: // Enter key
                choice = highlight;
                break;
            default:
                break;
        }
        print_menu(menu_win, highlight, choices, n_choices);
        if(choice != 0) // User did a choice come out of the infinite loop
            break;
    }
    mvprintw(0, 0, "You chose choice %d with choice string %s\n", choice, choices[choice - 1]);
    clrtoeol();
    refresh();
    getch();
    endwin();             // End ncurses
    return 0;
}