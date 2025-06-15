#ifndef SERPENTE_HPP
#define SERPENTE_HPP

#include "../includes/include.h"
#include "../utils/utils.h"

enum Direction {
    UP,    
    DOWN,  
    LEFT,  
    RIGHT 
};
struct body {
    int y;           
    int x;           
    body* next;      
};

class Serpente {
public:

    Direction dir;   
    
    Serpente(WINDOW* win, char c, int length);
    
    body* getHeadPos();
    
    body* tail();
    
    body* prevTail();
    
    body* addBody(int y, int x);
    
    void defaultMove();
    
    void moveUp();
    
    void moveDown();
    
    void moveLeft();
    
    void moveRight();
    
    void setMove(int key);
    
    bool firstMove();
    
    bool autoCollision();
    
    void display();
    
    void blank();
    
    int getSleepTime() {
        return SleepTime;
    }
    
    void setSleepTime(int time) {
        SleepTime = time;
    }

private:
    
    int headX, headY;   
    body* head;      
    char character;      
    WINDOW* win;       
    int SleepTime = 0;
    void moveBy(int dx, int dy);
};

#endif


