#pragma once
#include "Serpente.cpp"
#include "Mela.cpp"
#include "Livelli.cpp"
#include <cstring>



int wrapY = Maxy + 2;
int wrapX = Maxx + 3;

int tempoPassato = 0;  
int scoreSnake = 0;    

bool showPauseMenu(WINDOW* gameWin);

void initializeGame(WINDOW* win, Serpente*& serpent, Mela*& frutto, level*& livello) {
    serpent = new Serpente(win, 'o', 9);
    frutto = new Mela(win, -1, -1, '$');
    livello = new level();
    livello->setLevel(levelChosen);
}


void displayScore(WINDOW* win) {
    mvwprintw(win, wrapY - 1, 2, "Punteggio: %d", scoreSnake);
    wrefresh(win);
}

void displayTime(WINDOW* win) {
    mvwprintw(win, wrapY - 1, wrapX - 15, "Tempo: %d", tempoPassato);
    wrefresh(win);
}

void displayLevel(WINDOW *win, level* livello) {
    mvwprintw(win, 0, 2, "Livello: %d", levelChosen);
    wrefresh(win);
}

void displayStartMessage(WINDOW* win) {
    mvwprintw(win, 1, 10, "Press something to start..");
    wrefresh(win);
}


bool isCellEmpty(WINDOW* win, int y, int x) {
    chtype ch = mvwinch(win, y, x);
    char currentChar = ch & A_CHARTEXT;
    return (currentChar == ' ');
}

void spawnFruit(WINDOW* win, Mela* frutto, int &fruitX, int &fruitY) {
    
    fruitX = (rand() % (Maxx - 3)) + 1;
    fruitY = (rand() % (Maxy - 3)) + 1;
    
    while (!isCellEmpty(win, fruitY, fruitX)) {
        fruitX = rand() % (Maxx - 3) + 1;
        fruitY = (rand() % (Maxy - 3)) + 1;
    }
    
    frutto->Spawn(fruitX, fruitY);
}

void setupGameWindows(WINDOW*& win, WINDOW*& wrap, int& xMax, int& yMax) {
    getmaxyx(stdscr, yMax, xMax);
    
    win = newwin(Maxy, Maxx, yMax/2 - Maxy/2, xMax/2 - Maxx/2);
    
    wrap = newwin(wrapY, wrapX, yMax/2 - Maxy/2 - 1, xMax/2 - Maxx/2 - 1);
    
    wrefresh(wrap);
    box(win, 0, 0);
}


bool processUserInput(WINDOW* win, Serpente* serpent, 
                     
    int moveDelay, clock_t& lastMoveCheck, clock_t now) {
    if (now - lastMoveCheck < moveDelay) return false;
    
    
    int lastKey = ERR;
    int key;
    while ((key = wgetch(win)) != ERR) {
        lastKey = key;
    }
    
    if (lastKey == ESC_KEY) {
        bool shouldResume = showPauseMenu(win);
        if (!shouldResume) {
            return true; 
        }
    } 
    else if (lastKey != ERR) {
        serpent->setMove(lastKey);
    }
    
    serpent->defaultMove();
    lastMoveCheck = now;
    return false;
}


int start_game() {
    srand(time(NULL));
    initscr();
    curs_set(0);  
    scoreSnake = 0;
    tempoPassato = 0;
    int fruitX, fruitY;

    
    WINDOW *win, *wrap;
    int xMax, yMax;  
    setupGameWindows(win, wrap, xMax, yMax);

    
    Serpente *serpent;
    Mela *frutto;
    level *livello;
    initializeGame(win, serpent, frutto, livello);

    clock_t lastAppleCheck = clock();
    clock_t lastMoveCheck = clock();
    clock_t lastTime = clock();
    
    int appleDelay = CLOCKS_PER_SEC;  
    double moveDelay = CLOCKS_PER_SEC / (7.0 + (levelChosen - 1) * 0.666);  
    int levelDelay = 45;  
    int bonusPoints = 100 * livello->getId();
    
    displayStartMessage(win);
    int firstKey = wgetch(win);
    if (firstKey == ESC_KEY) {
        bool shouldResume = showPauseMenu(win);
        if (!shouldResume) {
            delete serpent;
            delete frutto;
            delete livello;
            delwin(win);
            delwin(wrap);
            return BYPASSGAMEOVER;
        }
    }

    lastTime = clock();
    lastMoveCheck = clock();
    
    flushinp();          
    nodelay(win, TRUE);  
    
    
    mvwprintw(win, 1, 10, "                          ");
    wrefresh(win);

    bool gameOver = false;
    
    while (true) {
        punteggioFinale = scoreSnake;  
        clock_t now = clock();
        if (processUserInput(win, serpent, moveDelay, lastMoveCheck, now)) {
            
            delete serpent;
            delete frutto;
            delete livello;
            delwin(win);
            delwin(wrap);
            return BYPASSGAMEOVER;
        }

        if (now - lastTime >= CLOCKS_PER_SEC) {
            tempoPassato++;  
            lastTime = now;
        }

        displayScore(wrap);   
        displayTime(wrap);    
        displayLevel(wrap, livello);  

        if (serpent->autoCollision() && !serpent->firstMove()) {
            gameOver = true;
        }

        if(frutto->check(serpent)){
            mvwaddch(win, frutto->yPos(), frutto->xPos(), ' ');
            lastAppleCheck = clock();
            frutto->off();
            scoreSnake += bonusPoints;
            punteggioFinale = scoreSnake;  
        }

        if (!frutto->isOn() && now - lastAppleCheck >= appleDelay) {
            spawnFruit(win, frutto, fruitX, fruitY);
        }

        if(tempoPassato >= levelDelay){
            Utils::wait(500);
            
            werase(win);
            box(win, 0, 0);
            mvwprintw(win, Maxy/2 - 1, Maxx/2 - 10, "Livello Completato!");
            mvwprintw(win, Maxy/2, Maxx/2 - 10, "Punti Bonus: %d", bonusPoints);
            mvwprintw(win, Maxy/2 + 1, Maxx/2 - 10, "Premi ESC per continuare");
            scoreSnake += bonusPoints;
            punteggioFinale = scoreSnake;  
            displayScore(wrap);
            wrefresh(win);

            while(true){
                int c = wgetch(win);
                if (c == ESC_KEY || c == ENTER_KEY) {
                    
                    delete serpent;
                    delete frutto;
                    delete livello;
                    delwin(win);
                    delwin(wrap);
                    break;
                }  
            }
            return BYPASSGAMEOVER;
        }

        serpent->display();  
        box(win, 0, 0);      
        wrefresh(win);       

        if (gameOver) {
            
            delete serpent;
            delete frutto;
            delete livello;

            delwin(win);
            delwin(wrap);            
            return GAME_OVER_COLLISION; 
        }
    }
}


bool showPauseMenu(WINDOW* gameWin) {
    flushinp();
    
    int menuHeight = 8;
    int menuWidth = 20;
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    int startY = (yMax - menuHeight) / 2;
    int startX = (xMax - menuWidth) / 2;
    
    WINDOW* pauseWin = newwin(menuHeight, menuWidth, startY, startX);
    keypad(pauseWin, TRUE);        
    nodelay(pauseWin, FALSE);      
    
    const char* options[] = {"Ritorna al gioco", "Torna al menu"};
    int numOptions = 2;
    int highlight = 1;  
    int choice = 0;  
    
    
    while (true) {
        
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
        
        
        flushinp();  
        int c = wgetch(pauseWin);
        
        switch (c) {
            case KEY_UP:
                
                highlight = (highlight == 1) ? numOptions : highlight - 1;
                break;
            case KEY_DOWN:
                
                highlight = (highlight == numOptions) ? 1 : highlight + 1;
                break;
            case ENTER_KEY: 
                choice = highlight;
                break;
            case ESC_KEY: 
                choice = 1;
                break;
        }
        
        
        if (choice != 0) break;
    }
    
    delwin(pauseWin);
    flushinp();           
    wrefresh(gameWin);    
    return (choice == 1); 
}