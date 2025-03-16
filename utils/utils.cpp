#include "utils.h"
#pragma once


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