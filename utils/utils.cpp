#include "utils.h"
#pragma once

int punteggioFinale = 0;

void initialize_ncurses() {
    initscr();            
    clear();
    noecho();
    cbreak();             
}

void Utils::wait(int milliseconds){
    clock_t start_time = clock();
    clock_t end_time = start_time + milliseconds * CLOCKS_PER_SEC / 1000;
    
    while (clock() < end_time) {
        
    }
}

void Utils::initColors() {
    start_color();
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
    init_pair(4, COLOR_GREEN, COLOR_BLACK);
}

WINDOW* Utils::CreateBoxWindowCentered(WINDOW* boxForFile, int heightDivisor, int widthDivisor) {
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    
    int height = yMax / heightDivisor;
    int width = xMax / widthDivisor;
    int starty = (LINES - height) / 2;
    int startx = (COLS - width) / 2;

    boxForFile = newwin(height, width, starty, startx);
    refresh();
    box(boxForFile, 0, 0);
    
    return boxForFile;
}

WINDOW* Utils::CreateTextBox(WINDOW* boxForFile, int characters, int starty, int startx){
    
    int height = 7;
    int width = 30;

    boxForFile = newwin(height, width, starty, startx);
    refresh();
    box(boxForFile, 0, 0);
    
    return boxForFile;
}

void Utils::InlinedTextWindow(WINDOW* insideBox, int x, int y, char* buffer) {
    int initY = y;      
    int origX = x;  

    for (int i = 0; buffer[i] != '\0'; ++i) {
        if (buffer[i] == '\n') {
            y++;
            x = origX; 
            continue;
        }
        
       
        int relLine = y - initY;
        int cp = (relLine < 3) ? (relLine + 1) : 0;  
        
        if (cp != 0)
            wattron(insideBox, COLOR_PAIR(cp));
        mvwaddch(insideBox, y, x++, buffer[i]);
        if (cp != 0)
            wattroff(insideBox, COLOR_PAIR(cp));
    }
}