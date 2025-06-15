#ifndef MELA_HPP
#define MELA_HPP

#include "../includes/include.h"

class Serpente;
class Mela {
public:
    
    Mela(WINDOW* win, int x, int y, char c);

    void randPos(int x, int y);

    void Spawn(int x, int y);

    bool isOn();

    void off();

    bool check(Serpente* serp);

    int xPos();

    int yPos();

private:
    
    WINDOW* win;        
    int x;             
    int y;             
    char character;     
    bool active;        
};

#endif
