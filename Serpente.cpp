#pragma once
#include "Serpente.hpp"
#include "Mela.hpp"

bool isCellEmpty(WINDOW* win, int y, int x) {
    chtype ch = mvwinch(win, y, x);
    char currentChar = ch & A_CHARTEXT;
    return (currentChar == ' ');
}

void initializeGame(WINDOW* win, Serpente*& serpent, Mela*& frutto) {
    serpent = new Serpente(win, '~', 7);
    frutto = new Mela(win, -1, -1, '$');
}

void displayStartMessage(WINDOW* win) {
    mvwprintw(win, 1, 10, "Press something to start\n");
    wrefresh(win);
    wgetch(win); // Wait for user input
    mvwprintw(win, 1, 10, "                         "); // Clear the message
    wrefresh(win);
}

void spawnFruit(WINDOW* win, Mela* frutto, int& fruitX, int& fruitY, int Maxx, int Maxy) {
    fruitX = rand() % (Maxx - 2) + 1;
    fruitY = rand() % (Maxy - 2) + 1;
    while (!isCellEmpty(win, fruitY, fruitX)) {
        fruitX = rand() % (Maxx - 2) + 1;
        fruitY = rand() % (Maxy - 2) + 1;
    }
    frutto->Spawn(fruitX, fruitY);
}

void start_game() {
    srand(time(NULL));
    initscr();
    curs_set(0);
    noecho();

    int xMax, yMax;
    getmaxyx(stdscr, yMax, xMax);

    WINDOW* win = newwin(Maxy, Maxx, yMax / 2 - Maxy / 2, xMax / 2 - Maxx / 2);
    box(win, 0, 0);

    bool firstMove = true;
    int fruitX;
    int fruitY;

    Serpente* serpent;
    Mela* frutto;
    initializeGame(win, serpent, frutto);

    displayStartMessage(win);

    while (serpent->getMove() != (char)27) {
        if (firstMove) {
            firstMove = false;
            nodelay(win, true);
        }

        if (!frutto->isOn()) {
            spawnFruit(win, frutto, fruitX, fruitY, Maxx, Maxy);
        }

        serpent->display();
        wrefresh(win);
    }

    endwin();
}

// bool screen [Maxy][Maxx]{}; 
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



