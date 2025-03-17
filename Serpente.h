#include "main.h"
#pragma once

// Classe del serpente.
class Serpente { 
    public:
        Serpente(WINDOW * win, int y, int x, char c);

        void blank();
        
        void moveUp();

        void moveDown();
        
        void moveLeft();
        
        void moveRight();
        
        int getMove();
        
        void display();

    private:
        int y, x, yMax, xMax;
        char character;
        WINDOW * win;
};

//Costruttore base del serpente(finestra di stampa, coordinate di inizio e carattere di stampa).
Serpente::Serpente(WINDOW * win, int y, int x, char c){
    this->win = win;
    this->y = y;
    this->x = x;
    getmaxyx(this->win, yMax, xMax);
    keypad(this->win, true);
    character = c;
}

// movimento in alto.
void Serpente::moveUp(){
    y = y-1;
    if(y < 1){
        y = yMax-2;
    }
}

// movimento in basso.
void Serpente::moveDown(){
    y = y+1;
    if(y > yMax-2){
        y = 1;
    }
}

// movimento a sinistra.
void Serpente::moveLeft(){
    x = x-1;
    if(x < 1){
        x = xMax-2;
    }
}

// movimento a destra.
void Serpente::moveRight(){
    x = x+1;
    if(x > xMax-2){
        x = 1;
    }
}

// funzione che prende da tastiera (KEY UP, KEY DOWN, KEY LEFT, KEY RIGHT).
int Serpente::getMove(){
    int moveKey = wgetch(this->win);
    switch(moveKey){
        case KEY_UP:
            
            moveUp();
            
            break;
        case KEY_DOWN:
            
            moveDown();
            
            break;
        case KEY_LEFT:
            
            moveLeft();
                  
            break;
        case KEY_RIGHT:
            
            moveRight();
            
            break;
        default:
            break;
    }

    return moveKey;
}

// aggiorna in memoria della finestra il carattere con le coordinate.
void Serpente::display(){
    mvwaddch(this->win, y, x, character);
}

// rimpiazza il carattere presente con uno spazio bianco(ci sto lavorando -_-).
void Serpente::blank(){
    mvwaddch(this->win, y, x, ' ');
}