#ifndef UTILS_H
#define UTILS_H
#pragma once
#include "../includes/include.h"



// same here fiocane
class Utils {
public:
    static WINDOW* CreateBoxWindowCentered(WINDOW* boxForFile, int heightDivisor, int widthDivisor);
    static WINDOW* CreateTextBox(WINDOW* boxForFile, int characters, int starty, int startx);
    static void InlinedTextWindow( WINDOW* insideBox, int x, int y, char* buffer);
};


#endif // UTILS_H

