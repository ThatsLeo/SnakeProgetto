#include "main_menu.h"
#include "../gioco/game.cpp"
#include "../classifica.cpp"
#include "../gioco/Livelli.cpp"

Menu::Menu() 
    : highlight(1), choice(0), n_choices(4), old_choice(0) {
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
}

void Menu::gameOver(int game_state){
    if(game_state == 0){
                mvprintw(2, startx +3, "Game Over\n");
                mvprintw(3, startx +3, "Press esc to return to menu\n");
                
            }else{
                mvprintw(0, startx, "Game Over\n");
                mvprintw(1, startx, "New Record!\n");
                mvprintw(2, startx, "Press esc to return to menu\n");
                FileManager fileManager = FileManager();
                char  ssssss[100];
                sprintf(ssssss, "Guest:%d \n",game_state);
                fileManager.writeFileAppend(ssssss);
            }
}


void Menu::print_menu() {
    box(menu_win, 0, 0);
    for(int i = 0; i < n_choices; ++i) {
        
        int x = getmaxx(menu_win) /2 - std::strlen(choices[i]) / 2;
        int y = getmaxy(menu_win)/ 2 + i - n_choices /2;
        
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
level levelMenu; // Creazione della lista dei livelli
bool pressed_exit = 0;
int game_state;

void Menu::start_menu() {
    
    FileManager fileManager = FileManager();

    fileManager.writeFile("Classifica\n");
    fileManager.writeFileAppend("Fra:200 \n");
    fileManager.writeFileAppend("leo:100 \n");

    while (true) {
        curs_set(0); // Nascondi il cursore
        noecho(); // Non mostrare l'input dell'utente
        highlight = old_choice; 
        choice = 0;
        clear(); 
        refresh(); 
        wclear(menu_win); 
        wrefresh(menu_win); 

        int choice = handle_user_input(); // usate la scelta
        // Fate qualcosa con la scelta per esempio se fai gioca (1)
        // aggiungete la vostra classe con la griglia e snake etc.
        old_choice = choice; // Salva la scelta precedente per il refresh del menu

        // Ex. if (choice == 1) { Game game = Game(); game.start_game(); } 
        if (choice == 1) {   // Usiamo uno switch per gestire le scelte appena le abbiamo tutte
            game_state = start_game();
            gameOver(game_state);
            
        }else if (choice == 2) { 
            Utils::initColors();
            Classifica::start_classifica();
        }else if (choice == 3){
            wclear(menu_win);
            wrefresh(menu_win);
            WINDOW * insideBox;
            insideBox = Utils::CreateBoxWindowCentered(insideBox, 2, 4); 
            keypad(insideBox, TRUE);
            while(true){
                levelMenu.PrintLevels(insideBox);
                int c = levelMenu.processInput(wgetch(insideBox));
                if (c > 0){
                    game_state = start_game();
                    gameOver(game_state);
                    break;
                }
                else if (c == -2) break;
            }
            

            wrefresh(insideBox);
            // wclear(menu_win);
            // wrefresh(menu_win);
            // levelMenu.PrintLevels();
            // int c;
            // while (true) {
            //     c = wgetch(menu_win);
            //     if (c == KEY_UP) {
            //         levelMenu.prevLevel();
            //     } else if (c == KEY_DOWN) {
            //         levelMenu.nextLevel();
            //     } else if (c == 10) { // Enter key
            //         break; // Exit the loop to return to the menu
            //     }
            //     clear();
            //     levelMenu.PrintLevels();
            // }
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
        } 
    }
    
}
