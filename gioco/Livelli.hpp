#ifndef LIVELLI_HPP
#define LIVELLI_HPP

#include "../includes/include.h"


class level {
public:
    level();
    level(int id, level* next, level* prev);

    void nextLevel();

    void prevLevel();

    void setLevel(int id);

    void PrintLevels(WINDOW* win);

    int processInput(int c);

    int getId();

    int n_levels;

private:
    
    int id;             
    level* next;        
    level* prev;        
    level* currentlvl;  
    level* head;        
    level* tail;  
};

#endif