#ifndef UTILS_H
#define UTILS_H

#include "../includes/include.h"

class Utils {
public:

    static WINDOW* CreateBoxWindowCentered(WINDOW* boxForFile, int heightDivisor, int widthDivisor);

    static WINDOW* CreateTextBox(WINDOW* boxForFile, int characters, int starty, int startx);

    static void InlinedTextWindow(WINDOW* insideBox, int x, int y, char* buffer);

    static void initColors();

    static void wait(int milliseconds);
};

#endif 