#include "main_menu.h"
#include "../gioco/game.cpp"
#include "../classifica.cpp"
#include "../gioco/Livelli.cpp"
#include <cstring>  // For string functions

// ========== GLOBAL VARIABLES ==========                  // Flag to skip menu input processing
char playerName[32] = "Guest";      // Global variable to store player name
WINDOW* titleWin = nullptr; // Pointer for title window

// ========== PLAYER NAME INPUT FUNCTION ==========
// Get player name at the start of the program
void getPlayerName()
{
    // === WINDOW SETUP ===
    int nameWinHeight = 6;
    int nameWinWidth = 40;
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    int nameStartY = (yMax - nameWinHeight) / 2;
    int nameStartX = (xMax - nameWinWidth) / 2;

    WINDOW *nameWin = newwin(nameWinHeight, nameWinWidth, nameStartY, nameStartX);
    keypad(nameWin, TRUE);

    // === DISPLAY SETUP ===
    clear();
    refresh();
    box(nameWin, 0, 0);

    // === INPUT HANDLING ===
    noecho();    // We'll handle display manually
    curs_set(1); // Show cursor

    // Get user input (max 30 characters)
    char tempName[32] = ""; // Initialize empty
    int nameIndex = 0;      // Track position in name

    mvwprintw(nameWin, 1, 2, "Inserisci il tuo nome:");
    mvwprintw(nameWin, 2, 2, "> ");
    wrefresh(nameWin); // Make sure prompt is displayed

    wmove(nameWin, 2, 4); // Position cursor after "> "

    // Input loop - handle each character manually
    int c;
    while ((c = wgetch(nameWin)))
    {
        if (c == 10 || c == 13 || c == KEY_ENTER)
        { // Enter key
            break;
        }
        else if (c == KEY_BACKSPACE || c == 127 || c == 8)
        { // Backspace
            if (nameIndex > 0)
            {
                nameIndex--;
                tempName[nameIndex] = '\0';
                // Move cursor back and clear character
                int curX = getcurx(nameWin);
                if (curX > 4)
                {
                    mvwprintw(nameWin, 2, curX - 1, " ");
                    wmove(nameWin, 2, curX - 1);
                    wrefresh(nameWin);
                }
            }
        }
        else if (c >= 32 && c <= 126 && nameIndex < 30)
        { // Printable characters
            tempName[nameIndex] = c;
            tempName[nameIndex + 1] = '\0';
            nameIndex++;
            // Display the character manually
            wprintw(nameWin, "%c", c);
            wrefresh(nameWin);
        }
        // Handle arrow keys if needed
        else if (c == KEY_LEFT)
        {
            int curX = getcurx(nameWin);
            if (curX > 4)
            {
                wmove(nameWin, 2, curX - 1);
            }
        }
        else if (c == KEY_RIGHT)
        {
            int curX = getcurx(nameWin);
            if (curX < 4 + nameIndex && curX < nameWinWidth - 2)
            {
                wmove(nameWin, 2, curX + 1);
            }
        }

        wrefresh(nameWin); // Update display
    }

    // REMOVE THIS LINE - it was causing the problem:
    // mvwgetnstr(nameWin, 2, 4, tempName, 30);

    // Copy to global variable with safety checks
    strncpy(playerName, tempName, 31);
    playerName[31] = '\0'; // Ensure null termination

    // Use default name if input is empty
    if (strlen(playerName) == 0)
    {
        strcpy(playerName, "Guest");
    }

    // === CLEANUP ===
    curs_set(0); // Hide cursor

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

// ========== SCORE SAVING FUNCTION ==========
// Save player score to file (only if score is positive)
void SalvaPunteggio(int score) {
    if(score <= 0) return; // Don't save non-positive scores
    
    FileManager fileManager = FileManager();
    char scoreEntry[100];
    sprintf(scoreEntry, "%s:%d \n", playerName, score);
    fileManager.writeFileAppend(scoreEntry);
}

// ========== GAME OVER HANDLING ==========
// Handle different game ending scenarios and display appropriate messages
void Menu::gameOver(int game_state) {
    if(game_state == GAME_OVER_COLLISION) {
        // Game ended due to collision
        Utils::wait(200);
        SalvaPunteggio(punteggioFinale);
        mvprintw(2, startx + 3, "Game Over\n");
        mvprintw(3, startx + 3, "Press esc to return to menu\n");
        refresh();
        int c;
            while(c = wgetch(menu_win)){
                if (c == (char)27 || c == (char)10) break;
            }
    } 
    else if(game_state == BYPASSGAMEOVER) {
        // Player returned to menu or completed level - save score
        SalvaPunteggio(punteggioFinale);
    } 
    else {
        // New high score achieved
        mvprintw(0, startx, "Game Over\n");
        mvprintw(1, startx, "New Record!\n");
        mvprintw(2, startx, "Press esc to return to menu\n");        
        SalvaPunteggio(game_state);
    }
}


// ========== TITLE DISPLAY FUNCTION ==========
// Display the SNAKE title in its own window above the main menu
void Menu::displayTitle() {
    // Calculate title window dimensions and position
    int titleHeight = 7;
    int titleWidth = 32;
    
    int titleStartY = 0; // Position above main menu
    int titleStartX = (COLS - titleWidth) / 2;  // Center horizontally
    
    // Clean up existing title window if it exists
    if (titleWin != nullptr) {
        delwin(titleWin);
    }
    
    // Create title window
    titleWin = newwin(titleHeight, titleWidth, titleStartY, titleStartX);
    box(titleWin, 0, 0);
    
    // Display ASCII art SNAKE title
    mvwprintw(titleWin, 1, 2, " SSS  S  S  SSSS  S  S SSSSS");
    mvwprintw(titleWin, 2, 2, "S     SS S S   S  S S  S    ");
    mvwprintw(titleWin, 3, 2, " SSS  S SS SSSSS  SS   SSSS ");
    mvwprintw(titleWin, 4, 2, "    S S  S S   S  S S  S    ");
    mvwprintw(titleWin, 5, 2, " SSS  S  S S   S  S  S SSSSS");
    
    wrefresh(titleWin);
}

// ========== TITLE CLEANUP FUNCTION ==========
// Remove the title window from screen
void Menu::removeTitle() {
    if (titleWin != nullptr) {
        wclear(titleWin);
        wrefresh(titleWin);
        delwin(titleWin);
        titleWin = nullptr;
    }
    clear();
    refresh();
}

void Menu::print_menu() {
    box(menu_win, 0, 0);
    
    // ========== DISPLAY MENU OPTIONS ==========
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
    displayTitle();  // Display title in its own box
    print_menu();
    while(1) {
        c = wgetch(menu_win);
        process_input(c);
        displayTitle();  // Redraw title
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
        wrefresh(menu_win);        int choice = handle_user_input(); 
        old_choice = choice; // Salva la scelta precedente per il refresh del menu
        
        if (choice == 1) {   // Start Game
            removeTitle();  // Remove title before starting game
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
                else if (c == -2){
                    break;
                }   
        }
            wrefresh(insideBox);
            refresh();
        }
         else if (choice == 4) {
            break;
        }else{
            mvprintw(0, 0, "Per la scelta n: %d o %s dovete ancora fare sta schermata\n", choice, choices[choice - 1]);
        }

        // invece che printare sta linea usate il vostro.

        clrtoeol();
        
        refresh();
    }
    
}
