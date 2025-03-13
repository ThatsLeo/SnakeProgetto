#include <../main.h>

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

void initialize_ncurses() {
    initscr();            // Initialize ncurses
    clear();
    noecho();
    cbreak();             // Line buffering disabled. Pass on everything
}

WINDOW* create_menu_window(int height, int width, int starty, int startx) {
    WINDOW *menu_win = newwin(height, width, starty, startx);
    keypad(menu_win, TRUE);
    return menu_win;
}

void process_input(int c, int &highlight, int n_choices, int &choice) {
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
}

int handle_user_input(WINDOW *menu_win, const char *choices[], int n_choices) {
    int highlight = 1;
    int choice = 0;
    int c;
    print_menu(menu_win, highlight, choices, n_choices);
    while(1) {
        c = wgetch(menu_win);
        process_input(c, highlight, n_choices, choice);
        print_menu(menu_win, highlight, choices, n_choices);
        if(choice != 0) // User did a choice come out of the infinite loop
            break;
    }
    return choice;
}