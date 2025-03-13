#include "main_menu.h"

Menu::Menu() 
    : highlight(1), choice(0), n_choices(4) {
    choices[0] = "Gioca";
    choices[1] = "Classifica";
    choices[2] = "Livelli";
    choices[3] = "Exit";

    
    initialize_ncurses();

    
    
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
    int x = 3, y = 2;  // offset scritte per esempio y piu e alto il numero piu in basso e la scritta, stessa cosa per x
    box(menu_win, 0, 0);
    for(int i = 0; i < n_choices; ++i) {
        if(highlight == i + 1) { 
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", choices[i]);
            wattroff(menu_win, A_REVERSE); // wattroff effetto highlight
        } else {
            mvwprintw(menu_win, y, x, "%s", choices[i]); // senza effetto highlight
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
        highlight = 1; 
        choice = 0;    
        clear(); 
        //refresh(); 
        wclear(menu_win); 
        wrefresh(menu_win); 
        int choice = handle_user_input(); // usate la scelta

        // Fate qualcosa con la scelta per esempio se fai gioca (1)
        // aggiungete la vostra classe con la griglia e snake etc.

        // Ex. if (choice == 1) { Game game = Game(); game.start_game(); } 

        mvprintw(0, 0, "Per la scelta n: %d o %s dovete ancora fare sta schermata\n", choice, choices[choice - 1]);
        // invece che printare sta linea usate il vostro.

        clrtoeol();
        refresh();
        int c = getch();
        if (c == 27) {   // 27 ovvero esc usatelo nel vostro codice pure per tornare al menu
            clear();
            refresh();
            continue; 
        } else {
            break;
        }
    }
    
    endwin();
}