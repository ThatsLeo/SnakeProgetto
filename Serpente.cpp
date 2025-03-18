#include "Serpente.h"
bool screen [Maxy][Maxx]{}; 
int main(int argc, char ** argv){
    initscr();
    noecho();
    int xMax, yMax;
    
    getmaxyx(stdscr, yMax, xMax);
    
    WINDOW * win = newwin(Maxy, Maxx, yMax/2 - Maxy/2, xMax/2 - Maxx/2);
    
    box(win, 0, 0);
    
    Serpente *serpent = new Serpente(win, '~', 7);
    while(serpent->getMove() != (char)27){
        serpent->display();
        wrefresh(win);
    }
    
    
    
    endwin();
    return 0;
}



