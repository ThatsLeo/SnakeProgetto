#pragma once
#include "Serpente.hpp"
#include "Mela.hpp"

bool isCellEmpty(WINDOW* win, int y, int x) {
    chtype ch = mvwinch(win, y, x);
    char currentChar = ch & A_CHARTEXT;
    return (currentChar == ' ');
}

int start_game(){
    srand(time(NULL));
    initscr();
    curs_set(0);
    noecho();

    int xMax, yMax;
    
    getmaxyx(stdscr, yMax, xMax);
    
    WINDOW *win = newwin(Maxy, Maxx, yMax/2 - Maxy/2, xMax/2 - Maxx/2);
    box(win, 0, 0);

    bool firstMove = true;
    int fruitX;
    int fruitY;
    
    Serpente *serpent = new Serpente(win, '~', 7);
    Mela *frutto = new Mela(win, -1, -1, '$');
    

    mvwprintw(win, 1, 10, "Press something to start\n" );
    wrefresh(win);

    while(serpent->getMove() != (char)27){
        

        if(firstMove){
            mvwprintw(win, 1, 10, "                         " );
            wrefresh(win);
            firstMove = false;
            nodelay(win, true);
        }

        if(!frutto->isOn()){
            
            fruitX = rand() % (Maxx - 2) + 1;
            fruitY = rand() % (Maxy - 2) + 1;
            if(!isCellEmpty(win, fruitY, fruitX)){
                fruitX = rand() % (Maxx - 2) + 1;
                fruitY = rand() % (Maxy - 2) + 1;
            }
            frutto->Spawn(fruitX, fruitY);

        }
        
        serpent->display();
        wrefresh(win);
    }
    endwin();
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



