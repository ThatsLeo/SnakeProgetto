#include "main_menu.h"
#include "../gioco/game.cpp"
#include "../classifica.cpp"
#include "../gioco/Livelli.cpp"
#include <cstring>  // For string functions

int SkipInput = 0;
char playerName[32] = "Guest"; // Global variable to store player name
// Function to get player name input
void getPlayerName() {
    // Create a small centered window for name input
    int nameWinHeight = 6;
    int nameWinWidth = 40;
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    int nameStartY = (yMax - nameWinHeight) / 2;
    int nameStartX = (xMax - nameWinWidth) / 2;
    
    WINDOW* nameWin = newwin(nameWinHeight, nameWinWidth, nameStartY, nameStartX);
    keypad(nameWin, FALSE);
    
    // Clear screen and draw the input window
    clear();
    refresh();
    box(nameWin, 0, 0);
    
    // Display prompt
    mvwprintw(nameWin, 1, 2, "Inserisci il tuo nome:");
    mvwprintw(nameWin, 2, 2, "> ");
    wrefresh(nameWin);
    
    // Enable input display and cursor
    echo();
    curs_set(1);
    
    // Get user input
    char tempName[32];
    mvwgetnstr(nameWin, 2, 4, tempName, 30); // Max 30 characters
    
    // Copy to global variable, ensuring null termination
    strncpy(playerName, tempName, 31);
    playerName[31] = '\0';
    
    // If empty name, use default
    if (strlen(playerName) == 0) {
        strcpy(playerName, "Guest");
    }
    
    // Restore ncurses settings
    noecho();
    curs_set(0);
    
    // Clean up
    delwin(nameWin);
    clear();
    refresh();
}

Menu::Menu() 
    : highlight(1), choice(0), n_choices(4), old_choice(0) {
    choices[0] = "Gioca";
    choices[1] = "Classifica";
    choices[2] = "Livelli";
    choices[3] = "Esci";

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

void SalvaPunteggio(int score) {
    if(score <= 0) return; // Non salvare punteggi negativi
    FileManager fileManager = FileManager();
    char scoreEntry[100];
    sprintf(scoreEntry, "%s:%d \n", playerName, score);
    fileManager.writeFileAppend(scoreEntry);
}

void Menu::gameOver(int game_state){
    
    if(game_state == 0){
                mvprintw(2, startx +3, "Game Over\n");
                mvprintw(3, startx +3, "Press esc to return to menu\n");
                // Utils::wait(2000); // Aspetta un secondo prima di mostrare il messaggio
                // SkipInput = 1;

            }else if(game_state == 12938){
                SalvaPunteggio(punteggioFinale);
                SkipInput = 1; // Imposta SkipInput a 1 o true per andare direttamente al menu

            }else{
                mvprintw(0, startx, "Game Over\n");
                mvprintw(1, startx, "New Record!\n");
                mvprintw(2, startx, "Press esc to return to menu\n");

                SalvaPunteggio(game_state);
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

void Menu::process_input(int c) {  // abbiamo sisteamato il metodo process_input per gestire l'input dell'utente
    // prima poteva andare out of bounds, ora no
    switch(c) {
        case KEY_UP:
            highlight--;
            if(highlight < 1)
                highlight = n_choices;
            break;
        case KEY_DOWN:
            highlight++;
            if(highlight > n_choices)
                highlight = 1;
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
    
    // Get player name before showing menu
    getPlayerName();
    
    FileManager fileManager = FileManager();

    fileManager.writeFile("Classifica\n"); // lascio questa cosi ogni volta resetta la classifica
    
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
        old_choice = choice; // Salva la scelta precedente per il refresh del menu        // Ex. if (choice == 1) { Game game = Game(); game.start_game(); } 
        switch (choice) {
            case 1:
                game_state = start_game();
                gameOver(game_state);
                break;
                
            case 2:
                Utils::initColors();
                Classifica::start_classifica();
                break;
                
            case 3:
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
                delwin(insideBox); // Clean up the window
                break;
                
            case 4:
                return; // Exit the menu loop
                
            default:
                mvprintw(0, 0, "Per la scelta n: %d o %s out of bound bug \n", choice, choices[choice - 1]);
                break;        }

        // Clear and refresh for next iteration
        clrtoeol();
        refresh();
        int c;

        if(!SkipInput){
            c = getch();
        }
        SkipInput = !SkipInput;

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
