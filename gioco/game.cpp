#pragma once
#include "Serpente.cpp"
#include "Mela.cpp"
#include "Livelli.cpp"
#include <cstring>

// Function declaration
bool showPauseMenu(WINDOW* gameWin);

int wrapY = Maxy + 2;
int wrapX = Maxx + 3;

int tempoPassato = 0;
int scoreSnake = 0;

// Initializes the serpent and fruit objects
void initializeGame(WINDOW* win, Serpente*& serpent, Mela*& frutto, level*& livello) {
    serpent = new Serpente(win, 'o', 7);
    frutto = new Mela(win, -1, -1, '$');
    livello = new level();
    livello->setLevel(levelChoosen);
}

void punteggio(WINDOW* win) {
    mvwprintw(win, wrapY - 1, 2, "Punteggio: %d", scoreSnake);
    wrefresh(win);
}

void tempo(WINDOW* win) {
    mvwprintw(win, wrapY - 1, wrapX - 15, "Tempo: %d", tempoPassato);
    wrefresh(win);
}

void printLivello(WINDOW *win, level* livello){
    mvwprintw(win, 0, 2, "Livello: %d", levelChoosen);
    wrefresh(win);
}

// Returns true if the cell at (y, x) in the window is empty (a space)
bool isCellEmpty(WINDOW* win, int y, int x) {
    chtype ch = mvwinch(win, y, x);
    char currentChar = ch & A_CHARTEXT;
    return (currentChar == ' ');
}


// Displays the start message, waits for a key press, then clears it.
// Only uses a single input parameter.
void displayStartMessage(WINDOW* win) {
    mvwprintw(win, 1, 10, "Press something to start..");
    wrefresh(win);
   
}

// Genera il frutto in una posizione casuale e vuota.
void spawnFruit(WINDOW* win, Mela* frutto, int &fruitX, int &fruitY) {
    fruitX = (rand() % (Maxx - 3)) + 1;
    fruitY = (rand() % (Maxy - 3)) + 1;
    while (!isCellEmpty(win, fruitY, fruitX)) {
        fruitX = rand() % (Maxx - 3) + 1;
        fruitY = (rand() % (Maxy - 3)) + 1;
    }
    frutto->Spawn(fruitX, fruitY);
}

// The main game function is now a void function with no input parameters.
int start_game() {
    srand(time(NULL));
    initscr();
    curs_set(0);
    noecho();

    scoreSnake = 0;
    tempoPassato = 0;
    int xMax, yMax;
    getmaxyx(stdscr, yMax, xMax);
    int fruitX, fruitY;

    // Create the game window with dimensions based on global constants.
    WINDOW *win = newwin(Maxy, Maxx, yMax/2 - Maxy/2, xMax/2 - Maxx/2);
    WINDOW *wrap = newwin(wrapY, wrapX, yMax/2 - Maxy/2 - 1, xMax/2 - Maxx/2 - 1);
    wrefresh(wrap);
    box(win, 0, 0);

    Serpente *serpent;
    Mela *frutto;
    level *livello;
    initializeGame(win, serpent, frutto, livello);

    clock_t lastAppleCheck = clock();
    clock_t lastMoveCheck = clock();
    clock_t lastLevelCheck = clock();    
    int appleDelay = CLOCKS_PER_SEC;
    int moveDelay = ((CLOCKS_PER_SEC / 4) / levelChoosen);
    int levelDelay = 45; 

    displayStartMessage(win);

    int firstKey = wgetch(win);
    if (firstKey == (char)27) {  // If ESC is pressed, show pause menu
        bool shouldResume = showPauseMenu(win);
        if (!shouldResume) {
            return 0;
        }
    }

    clock_t lastTime = clock();
    clock_t startTimeFromGame = clock();
    lastMoveCheck = clock();
    nodelay(win, true);  // Abilita input non bloccante
    
    
    // Pulisci il messaggio iniziale
    mvwprintw(win, 1, 10, "                          ");
    wrefresh(win);

    bool gameOver = false;
    int bonusPoints = 100 * livello->getId();

    while (true) {
        punteggioFinale = scoreSnake;

        clock_t now = clock();        
        if(now - lastMoveCheck >= moveDelay){
            int key = serpent->getMove();
            if (key == (char)27) {
                // Show pause menu instead of breaking
                bool shouldResume = showPauseMenu(win);
                if (!shouldResume) {
                    return 100; // Exit game if user chose "Exit Game"
                }
                // If resuming, continue the game loop
            }
            lastMoveCheck = now;
        }

        if(now - lastTime >= CLOCKS_PER_SEC){
            tempoPassato++;
            lastTime = now;
        }
        punteggio(wrap);
        tempo(wrap);
        printLivello(wrap, livello);

        if (serpent->autoCollision() && !serpent->firstMove()) {
            gameOver = true;
        }

        if(frutto->check(serpent)){
            mvwaddch(win, frutto->yPos(), frutto->xPos(), ' ');
            lastAppleCheck = clock();
            frutto->off();
            scoreSnake += bonusPoints;
        }

        if (!frutto->isOn() && now - lastAppleCheck >= appleDelay) {
            spawnFruit(win, frutto, fruitX, fruitY);
        }

        if(tempoPassato >= levelDelay){
            gameOver = true;
            werase(win);
            box(win, 0, 0);
            mvwprintw(win, Maxy/2, Maxx/2 - 10, "Level Completed!");
            mvwprintw(win, Maxy/2 + 1, Maxx/2 - 10, "Bonus: %d", bonusPoints);
            scoreSnake += bonusPoints;
            wrefresh(win);
            getch();
        }

        serpent->display();
        box(win, 0, 0);
        wrefresh(win);

        if (gameOver){
            delete serpent;
            delete frutto;
            delete livello;
            break;
        }
        
    }
    delwin(win);
    delwin(wrap);
    if(tempoPassato > 0){
        
        return scoreSnake;
    }
    return 0;
}

bool showPauseMenu(WINDOW* gameWin) {
    // Create pause menu window
    int menuHeight = 8;
    int menuWidth = 20;
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    int startY = (yMax - menuHeight) / 2;
    int startX = (xMax - menuWidth) / 2;
    
    WINDOW* pauseWin = newwin(menuHeight, menuWidth, startY, startX);
    keypad(pauseWin, TRUE);
    
    const char* options[] = {"Ritorna al gioco", "Torna al menu"};
    int numOptions = 2;
    int highlight = 1;
    int choice = 0;
    
    while (true) {
        // Draw pause menu
        werase(pauseWin);
        box(pauseWin, 0, 0);
        mvwprintw(pauseWin, 1, (menuWidth - 13) / 2, "GIOCO IN PAUSA");
        
        for (int i = 0; i < numOptions; i++) {
            int y = 3 + i;
            int x = (menuWidth - strlen(options[i])) / 2;
            
            if (highlight == i + 1) {
                wattron(pauseWin, A_REVERSE);
                mvwprintw(pauseWin, y, x, "%s", options[i]);
                wattroff(pauseWin, A_REVERSE);
            } else {
                mvwprintw(pauseWin, y, x, "%s", options[i]);
            }
        }
        wrefresh(pauseWin);
        
        int c = wgetch(pauseWin);
        switch (c) {
            case KEY_UP:
                highlight = (highlight == 1) ? numOptions : highlight - 1;
                break;
            case KEY_DOWN:
                highlight = (highlight == numOptions) ? 1 : highlight + 1;
                break;
            case 10: // Enter
                choice = highlight;
                break;
            case 27: // ESC - resume game
                choice = 1;
                break;
        }
        
        if (choice != 0) break;
    }
    
    delwin(pauseWin);
    
    // Redraw the game window
    wrefresh(gameWin);
    
    return (choice == 1); // true = resume, false = exit
}



