#include "includes/include.h"
#include "MioSerpente.hpp"
#include "gioco/Mela.hpp"

bool isCellEmpty(WINDOW* win, int y, int x) {
    chtype ch = mvwinch(win, y, x);
    char currentChar = ch & A_CHARTEXT;
    return (currentChar == ' ');
}

    clock_t lastAppleCheck;
    clock_t lastMoveCheck;
    int appleDelay = CLOCKS_PER_SEC * 5;
    int moveDelay = CLOCKS_PER_SEC / 10;

bool screen [Maxy][Maxx]{}; 
int main(int argc, char ** argv){
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
    
    Serpente *serpent = new Serpente(win, 'o', 7);
    Mela *frutto = new Mela(win, -1, -1, '$');
    
    while(serpent->getMove() != (char)27){
        clock_t now = clock();

        if(now - lastMoveCheck >= moveDelay){
            lastMoveCheck = now;
        }



        if(firstMove){
            firstMove = false;
            nodelay(win, true);
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
        
        if(!frutto->isOn() && now - lastAppleCheck >= appleDelay){
            
            fruitX = rand() % (Maxx - 3) + 1;
            fruitY = rand() % (Maxy - 3) + 1;
            while(!isCellEmpty(win, fruitY, fruitX)){
                fruitX = rand() % (Maxx - 3) + 1;
                fruitY = rand() % (Maxy - 3) + 1;
            }
            frutto->randPos(fruitX, fruitY);
            mvwaddch(win, frutto->yPos(), frutto->xPos(), '$');

        }
        else{
            
            if(frutto->check(serpent)){
                frutto->off();
                mvwaddch(win, frutto->yPos(), frutto->xPos(), ' ');
                lastAppleCheck = now;
            }
        }

        serpent->display();
        box(win, 0, 0);
        wrefresh(win);
        
    }
    

    

    
    
    endwin();
    return 0;
}



