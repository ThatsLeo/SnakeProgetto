#ifndef UTILS_H
#define UTILS_H
#pragma once
#include "../includes/include.h"

#define BYPASSGAMEOVER 12938

extern int punteggioFinale;

// same here fiocane
class Utils {
public:
    static WINDOW* CreateBoxWindowCentered(WINDOW* boxForFile, int heightDivisor, int widthDivisor);
    static WINDOW* CreateTextBox(WINDOW* boxForFile, int characters, int starty, int startx);
    static void InlinedTextWindow( WINDOW* insideBox, int x, int y, char* buffer);
    static void initColors();    static void wait(int milliseconds);  // Made static since all other methods are static
};


#endif // UTILS_H