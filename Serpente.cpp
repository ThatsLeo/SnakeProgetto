#include "main.h"

int main(int argc, char ** argv){

    initscr();
    int xMax, yMax;
    
    WINDOW * win;
    win = newwin(11, 25, 5, 30);
    getmaxyx(win, yMax, xMax);
    refresh();
    win = newwin(11, 25, yMax, xMax);
    box(win, 0, 0);
    
    wrefresh(win);
    
    getch();
    getch();

    endwin();
    return 0;
}



