#pragma once
#include "Serpente.cpp"
#include "Mela.cpp"
#include "Livelli.cpp"

int tempoPassato = 0;
int scoreSnake = 0;


void punteggio() {
    mvprintw(Maxy/2, Maxx/3, "Punteggio: %d", scoreSnake);
    refresh();
}

void tempo() {
    mvprintw(Maxy/2 + 1, Maxx/3, "Tempo: %d", tempoPassato);
    refresh();
}

// Returns true if the cell at (y, x) in the window is empty (a space)
bool isCellEmpty(WINDOW* win, int y, int x) {
    chtype ch = mvwinch(win, y, x);
    char currentChar = ch & A_CHARTEXT;
    return (currentChar == ' ');
}

// Initializes the serpent and fruit objects
void initializeGame(WINDOW* win, Serpente*& serpent, Mela*& frutto, level*& livello) {
    serpent = new Serpente(win, 'o', 7);
    frutto = new Mela(win, -1, -1, '$');
    livello = new level();
    livello->setLevel(1);
    
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
    

    clock_t lastAppleCheck = clock();
    clock_t lastMoveCheck = clock();
    clock_t lastLevelCheck = clock();
    int appleDelay = CLOCKS_PER_SEC * 5;
    int moveDelay = CLOCKS_PER_SEC / 4;
    int levelDelay = CLOCKS_PER_SEC * 3;

    scoreSnake = 0;
    tempoPassato = 0;
    int xMax, yMax;
    getmaxyx(stdscr, yMax, xMax);

    // Create the game window with dimensions based on global constants.
    WINDOW *win = newwin(Maxy, Maxx, yMax/2 - Maxy/2, xMax/2 - Maxx/2);
    box(win, 0, 0);

    int fruitX, fruitY;

    Serpente *serpent;
    Mela *frutto;
    level *livello;
    initializeGame(win, serpent, frutto, livello);

    displayStartMessage(win);

    int firstKey = wgetch(win);
    if (firstKey == (char)27) {  // Se è ESC, esci subito
        endwin();
        return 0;
    }

    clock_t lastTime = clock();
    clock_t startTimeFromGame = clock();
    lastMoveCheck = clock();
    nodelay(win, true);  // Abilita input non bloccante
    
    
    // Pulisci il messaggio iniziale
    mvwprintw(win, 1, 10, "                          ");
    wrefresh(win);

    bool gameOver = false;

    while (true) {
        curs_set(0);
        
        clock_t now = clock();

        if(now - lastMoveCheck >= moveDelay){
            if (serpent->getMove() == (char)27) break;
            lastMoveCheck = now;
        }
        
        if(!frutto->isOn()){
            mvwprintw(stdscr, Maxy/2 + 2, Maxx/3, "         ");
            mvwprintw(stdscr, Maxy/2 + 2, Maxx/3, "Mangiato!");
            wrefresh(stdscr);
        }
        else {
            mvprintw(Maxy/2 + 2, Maxx/3, "         ");
            mvprintw(Maxy/2 + 2, Maxx/3, "%d %d", fruitX, fruitY);
            mvprintw(Maxy/2 + 3, Maxx/3, "         ");
            mvprintw(Maxy/2 + 3, Maxx/3, "%d %d", frutto->xPos(), frutto->yPos());
            wrefresh(stdscr);
        }

        if(now - lastTime >= CLOCKS_PER_SEC){
            tempoPassato++;
            lastTime = now;
        }
        punteggio();
        tempo();

        if (serpent->autoCollision() && !serpent->firstMove()) {
            gameOver = true;
        }

        if(frutto->check(serpent)){
            mvwaddch(win, frutto->yPos(), frutto->xPos(), ' ');
            lastAppleCheck = clock();
            frutto->off();
            scoreSnake += 100 * livello->getId();
        }

        if (!frutto->isOn() && now - lastAppleCheck >= appleDelay) {
            spawnFruit(win, frutto, fruitX, fruitY);
        }

        if(now - lastLevelCheck >= levelDelay){

            if(livello->getId() == livello->n_levels) livello->setLevel(1);
            mvwprintw(stdscr, Maxy/2 - 1, Maxx/3, "         ");
            mvwprintw(stdscr, Maxy/2 - 1, Maxx/3, "Livello %d", livello->getId());
            
            //livello->nextLevel();
            moveDelay = ((CLOCKS_PER_SEC / 4) / livello->getId());
            lastLevelCheck = now;
        }

        serpent->display();
        box(win, 0, 0);
        wrefresh(win);

        if (gameOver){
            delete serpent;
            delete frutto;
            delete livello;
            delwin(win);
            break;
        }
        
    }


    endwin();
    if(tempoPassato > 0){
        return scoreSnake;
    }
    return 0;
}



