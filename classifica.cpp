#pragma once
#include "classifica.h"

void Classifica::start_classifica(){
    srand(time(NULL));
    initscr();
    curs_set(0);
    noecho();

    FileManager fileManager = FileManager();

    const int bufferSize = 1024; // massimo 1024 caratteri compreso null-terminator
    char buffer[bufferSize];

    int chNumber = fileManager.readFile(buffer, bufferSize);

    WINDOW * insideBox;
    insideBox = Utils::CreateTextBox(insideBox, chNumber, 6, 4); 
    mvwprintw(insideBox, 1, 1, ("%s", buffer) );
    wrefresh(insideBox); 
}