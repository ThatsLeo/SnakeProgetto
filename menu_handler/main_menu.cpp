#include "main_menu.h"
#include "../Serpente.cpp"
#include "../classifica.cpp"

void initialize_ncurses() {
    initscr();            
    clear();
    noecho();
    cbreak();             
}

Menu::Menu() 
    : highlight(1), choice(0), n_choices(4) {
    choices[0] = "Gioca";
    choices[1] = "Classifica";
    choices[2] = "Livelli";
    choices[3] = "Exit";

    //initialize_ncurses();
    
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    
    int height = yMax/2;
    int width = xMax/3;
    starty = (LINES - height) / 2;
    startx = (COLS - width) / 2; // per centrare la finestra

    // Create the window for the menu
    menu_win = newwin(height, width, starty, startx);
    keypad(menu_win, TRUE);
    refresh();
}

Menu::~Menu() {
    delwin(menu_win);
    endwin();
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

bool pressed_exit = 0;
int game_state;
void Menu::start_menu() {
    while (true) {
        highlight = 1; 
        choice = 0;    
        clear(); 
        refresh(); 
        wclear(menu_win); 
        wrefresh(menu_win); 

        int choice = handle_user_input(); // usate la scelta
        // Fate qualcosa con la scelta per esempio se fai gioca (1)
        // aggiungete la vostra classe con la griglia e snake etc.

        // Ex. if (choice == 1) { Game game = Game(); game.start_game(); } 
        if (choice == 1) {   // Usiamo uno switch per gestire le scelte appena le abbiamo tutte
            game_state = start_game();
            
            if(game_state == 0){
                mvprintw(0, startx, "Game Over\n");
                mvprintw(2, startx, "Press esc to return to menu\n");
            }
        }else if (choice == 2) { 
            Classifica::start_classifica();
        }
         else if (choice == 4) { 
            break;
        }else{
            mvprintw(0, 0, "Per la scelta n: %d o %s dovete ancora fare sta schermata\n", choice, choices[choice - 1]);
        }

        // invece che printare sta linea usate il vostro.

        clrtoeol();
        refresh();
        int c;
        
        c = getch();
        
        
        if (c == 27 ) {   // 27 ovvero esc 
            pressed_exit = !pressed_exit;
            clear();
            refresh();
            wclear(menu_win); 
            wrefresh(menu_win);
            continue; 
        } else {
            break; //exit everything
        }
    }
    
    endwin();
}