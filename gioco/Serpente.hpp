#include "../includes/include.h"
#include "../utils/utils.h"
#pragma once

// Dizionario per tenere traccia della direzione del serpente.
enum Direction {UP, DOWN, LEFT, RIGHT};

// Struttura del corpo del serpente.
struct body{
    int y;
    int x;
    body * next;
};



// Classe del serpente.
class Serpente { 
    public:
        Direction dir;

        Serpente(WINDOW * win, char c, int lenght);

        body *getHeadPos();

        void defaultMove();

        void blank();

        body *prevTail();

        body *addBody(int y, int x);

        body* tail();
        
        void moveUp();

        void moveDown();
        
        void moveLeft();
        
        void moveRight();
        
        int getMove();
        
        void setMove(int key);
        
        void move();
        
        void display();

        int getSleepTime(){
            return SleepTime;
        }
        void setSleepTime(int time){
            SleepTime = time;
        }

        bool firstMove();

        bool autoCollision();

    private:
        
        int headX, headY;
        body *head;
        char character;
        WINDOW * win;
        int SleepTime = 0;

        void moveBy(int dx, int dy);
};


