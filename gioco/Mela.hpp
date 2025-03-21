#include "../includes/include.h"
#pragma once

class Mela{
    public:
        Mela(WINDOW * win, int x, int y, char c);

        inline void wait(int milliseconds);

        void randPos(int x, int y);

        void Spawn(int x, int y);

        bool isOn();

        void off();

        void check(Serpente *serp);


    private:
        WINDOW * win;
        int x;
        int y;
        char character;
};


// Inizializza la Mela.
Mela::Mela(WINDOW * win, int x, int y, char c){
    this->x = x;
    this->y = y;
    this->win = win;
    character = c;
}

void Mela::randPos(int x, int y){
    this->x = x;
    this->y = y;
}


void Mela::off(){
    x = -1;
    y = -1;
    wait(3000);
}

bool Mela::isOn(){
    if(x != -1 && y != -1) return true;
    return false;
}


void Mela::Spawn(int x, int y){
    randPos(x,y);
    mvwaddch(this->win, x, y, character);
}


inline void Mela::wait(int milliseconds){
    clock_t start_time = clock();
    clock_t end_time = start_time + milliseconds * CLOCKS_PER_SEC / 1000;

    while (clock() < end_time) {
        
    }
}

// Controlla se la posizione della mela e' la stessa della testa del serpente, se true disattiva la mela dalla griglia.
void Mela::check(Serpente *serp){
    body temp = *serp->getHeadPos();
    if(this->x == temp.x && this->y == temp.y){ 
        mvwaddch(this->win, y, x, ' ');
        off();
    }
}

