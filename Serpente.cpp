#include "Serpente.h"

int main(int argc, char ** argv){

    initscr();
    
    int xMax, yMax;
    
    getmaxyx(stdscr, yMax, xMax);
    
    WINDOW * win = newwin(yMax/2, xMax/5, yMax/4, xMax/5);
    
    box(win, 0, 0);
    
    wrefresh(win);
    
    Serpente *serp = new Serpente(win, yMax/2, xMax/2, '@');
    while(serp->getMove() != 'x'){
        serp->blank();
        serp->display();
        wrefresh(win);
    }
    
    
    
    endwin();
    return 0;
}



