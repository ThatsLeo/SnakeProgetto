#include "menu.h"

Menu::Menu() 
    : highlight(1), choice(0), n_choices(4) {
    choices[0] = "Gioca";
    choices[1] = "Classifica";
    choices[2] = "Livelli";
    choices[3] = "Exit";

    // Initialize ncurses
    initialize_ncurses();

    // Get the screen size
    int height = 10;
    int width = 30;
    int starty = (LINES - height) / 2;
    int startx = (COLS - width) / 2;

    // Create the window for the menu
    menu_win = newwin(height, width, starty, startx);
    keypad(menu_win, TRUE);
}

Menu::~Menu() {
    delwin(menu_win);
    endwin();
}

void Menu::initialize_ncurses() {
    initscr();            
    clear();
    noecho();
    cbreak();             
}

void Menu::print_menu() {
    int x = 2, y = 2;
    box(menu_win, 0, 0);
    for(int i = 0; i < n_choices; ++i) {
        if(highlight == i + 1) { 
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

void Menu::process_input(int c) {
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
        case 10: 
            choice = highlight;
            break;
        default:
            break;
    }
}

int Menu::handle_user_input() {
    int c;
    print_menu();
    while(1) {
        c = wgetch(menu_win);
        process_input(c);
        print_menu();
        if(choice != 0) 
            break;
    }
    return choice;
}

void Menu::start_menu() {
    while (true) {
        highlight = 1; // Reset highlight
        choice = 0;    // Reset choice
        clear(); // Clear the entire screen
        //refresh(); // Refresh the screen
        wclear(menu_win); // Clear the menu window
        wrefresh(menu_win); // Refresh the menu window
        int choice = handle_user_input();
        mvprintw(0, 0, "You chose choice %d with choice string %s\n", choice, choices[choice - 1]);
        clrtoeol();
        refresh();
        int c = getch();
        if (c == 27) { // ESC key
            clear();
            refresh();
            continue; // Go back to the main menu
        } else {
            break; // Exit the loop and end the program
        }
    }
    endwin();
}