#include "utils.h"
#pragma once

// Define the global variable
int punteggioFinale = 0;

void initialize_ncurses() {
    initscr();            
    clear();
    noecho();
    cbreak();             
}

inline void wait(int milliseconds){
    clock_t start_time = clock();
    clock_t end_time = start_time + milliseconds * CLOCKS_PER_SEC / 1000;


    while (clock() < end_time) {
        
    }

}

// Initialize colors for ncurses.
void Utils::initColors() {
    start_color();
    // Define color pair 1 as foreground red on background black.
    init_pair(1, COLOR_YELLOW, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLACK);
}

// use reference instead to make the method a void and remove complications
WINDOW* Utils::CreateBoxWindowCentered(WINDOW* boxForFile, int heightDivisor, int widthDivisor) {
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    
    int height = yMax / heightDivisor;
    int width = xMax / widthDivisor;
    int starty = (LINES - height) / 2;
    int startx = (COLS - width) / 2;

    // Create the window for the menu
    boxForFile = newwin(height, width, starty, startx);
    refresh();
    box(boxForFile, 0, 0);
    
    return boxForFile;
}

WINDOW* Utils::CreateTextBox(WINDOW* boxForFile, int characters, int starty, int startx){
    
    int height = 7;
    int width = 30;

    // Create the window for the menu
    boxForFile = newwin(height, width, starty, startx);
    refresh();
    box(boxForFile, 0, 0);
    
    return boxForFile;
}

void Utils::InlinedTextWindow(WINDOW* insideBox, int x, int y, char* buffer) {
    int initY = y;       // Save initial y coordinate.
    int origX = x;       // Save original x coordinate.

    // Lambda to determine the color pair based on the current line.
    auto getColorPair = [initY](int currentY) -> int {
        int relLine = currentY - initY;
        return (relLine < 3) ? (relLine + 1) : 0;  // Color pairs 1, 2, 3 for first three lines.
    };

    for (int i = 0; buffer[i] != '\0'; ++i) {
        if (buffer[i] == '\n') {
            y++;
            x = origX; // Reset x to the starting value for each new line.
            continue;
        }
        int cp = getColorPair(y);
        if (cp != 0)
            wattron(insideBox, COLOR_PAIR(cp));
        mvwaddch(insideBox, y, x++, buffer[i]);
        if (cp != 0)
            wattroff(insideBox, COLOR_PAIR(cp));
    }
}