#pragma once
#include "Serpente.hpp"
#include "Mela.hpp"

int tempoPassato = 0;
int scoreSnake = 0;

void punteggio() {

    mvprintw(Maxy/2, Maxx/3, "Punteggio:");
    if(tempoPassato > 10 ){
        mvprintw(Maxy/2 + 1, Maxx/3, "%d", tempoPassato*15 - 5*10);
        scoreSnake = tempoPassato*15 - 5*10;
    }else{
        mvprintw(Maxy/2 + 1, Maxx/3, "%d", tempoPassato*10);
        scoreSnake = tempoPassato*10;
    }
    
    refresh();
}

// Returns true if the cell at (y, x) in the window is empty (a space)
bool isCellEmpty(WINDOW* win, int y, int x) {
    chtype ch = mvwinch(win, y, x);
    char currentChar = ch & A_CHARTEXT;
    return (currentChar == ' ');
}

// Initializes the serpent and fruit objects
void initializeGame(WINDOW* win, Serpente*& serpent, Mela*& frutto) {
    serpent = new Serpente(win, 'o', 7);
    frutto = new Mela(win, -1, -1, '$');
}

// Displays the start message, waits for a key press, then clears it.
// Only uses a single input parameter.
void displayStartMessage(WINDOW* win) {
    mvwprintw(win, 1, 10, "Press something to start..");
    wrefresh(win);
   
}

// Spawns the fruit ensuring the cell is empty
// Uses exactly four parameters: the game window, the fruit object,
// and two integer references for the fruit's coordinates.
// The boundaries are determined using global constants Maxx and Maxy.
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

    clock_t lastAppleCheck;
    int appleDelay = CLOCKS_PER_SEC;
    int xMax, yMax;
    getmaxyx(stdscr, yMax, xMax);

    // Create the game window with dimensions based on global constants.
    WINDOW *win = newwin(Maxy, Maxx, yMax/2 - Maxy/2, xMax/2 - Maxx/2);
    box(win, 0, 0);

    bool firstMove = true;
    int fruitX, fruitY;

    Serpente *serpent;
    Mela *frutto;
    initializeGame(win, serpent, frutto);

    displayStartMessage(win);
    clock_t startTimeFromGame;
    
    while (serpent->getMove() != (char)27) {
        
        if(!frutto->isOn()){
            mvprintw(Maxy/2 + 2, Maxx/3, "         ");
            mvprintw(Maxy/2 + 2, Maxx/3, "Mangiato!");
        }
        else {
            mvprintw(Maxy/2 + 2, Maxx/3, "         ");
            mvprintw(Maxy/2 + 2, Maxx/3, "Non");
        }

        clock_t now = clock();
        if (firstMove) {
            // Clear the message by overwriting with spaces
            startTimeFromGame = clock();
            mvwprintw(win, 1, 10, "                          ");
            wrefresh(win);
            
            firstMove = false;
            nodelay(win, true);
        }

        tempoPassato = getElapsedTime(startTimeFromGame);
        punteggio();

        if(frutto->check(serpent)){
            mvwaddch(win, frutto->yPos(), frutto->xPos(), ' ');
            lastAppleCheck = clock();
            frutto->off();
        }

        if (!frutto->isOn() && now - lastAppleCheck >= appleDelay) {
            spawnFruit(win, frutto, fruitX, fruitY);
        }

        serpent->display();
        wrefresh(win);
        
    }

    endwin();
    if(tempoPassato > 0){
        return scoreSnake;
    }
    return 0;
}


bool screen [Maxy][Maxx]{}; 
// int main(int argc, char ** argv){
//     srand(time(NULL));
//     initscr();
//     curs_set(0);
//     noecho();
    
//     int xMax, yMax;
    
//     getmaxyx(stdscr, yMax, xMax);
    
//     WINDOW *win = newwin(Maxy, Maxx, yMax/2 - Maxy/2, xMax/2 - Maxx/2);
//     box(win, 0, 0);

//     bool firstMove = true;
//     int fruitX;
//     int fruitY;
    
//     Serpente *serpent = new Serpente(win, '~', 7);
//     Mela *frutto = new Mela(win, -1, -1, '$');
    
//     while(serpent->getMove() != (char)27){
        
//         if(firstMove){
//             firstMove = false;
//             nodelay(win, true);
//         }

//         if(!frutto->isOn()){
            
//             fruitX = rand() % (Maxx - 2) + 1;
//             fruitY = rand() % (Maxy - 2) + 1;
//             while(!isCellEmpty(win, fruitY, fruitX)){
//                 fruitX = rand() % (Maxx - 2) + 1;
//                 fruitY = rand() % (Maxy - 2) + 1;
//             }
//             frutto->Spawn(fruitX, fruitY);

//         }
        
//         serpent->display();
//         wrefresh(win);
//     }
    

    

    
    
//     endwin();
//     return 0;
// }



