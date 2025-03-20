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

WINDOW* Utils::CreateTextBox(WINDOW* boxForFile, int characters, int starty, int startx){


    
    int height = 5;
    int width = characters *1;

    // Create the window for the menu
    boxForFile = newwin(height, width, starty, startx);
    refresh();
    box(boxForFile, 0, 0);
    
    return boxForFile;
}

void Utils::InlinedTextWindow( WINDOW* insideBox, int x, int y, char* buffer) {
    int tempX = x;
    for (int i = 0; buffer[i] != '\0'; ++i) {
        
        if (buffer[i] == '\n') {
            y++;
            x = tempX; // Reset x to default for the new line
        } else {
            mvwaddch(insideBox, y, x++, buffer[i]);
        }
    }
}