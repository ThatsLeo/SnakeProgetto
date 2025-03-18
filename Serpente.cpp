#include "Serpente.h"

int main(int argc, char ** argv){

    initscr();
    
    int xMax, yMax;
    
    getmaxyx(stdscr, yMax, xMax);
    
    WINDOW * win = newwin(20, 50, yMax-20, xMax/3);
    
    box(win, 0, 0);
    
    wrefresh(win);
    
    Serpente *serpent = new Serpente(win, yMax/2, xMax/2, '~');
    while(serpent->getMove() != (char)27){
        serpent->display();
        wrefresh(win);
    }

    
    
    
    endwin();
    return 0;
}



