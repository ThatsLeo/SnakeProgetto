#include "../includes/include.h"
#include "Mela.hpp"

Mela::Mela(WINDOW * win, int x, int y, char c){
    Utils::initColors();
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
}

bool Mela::isOn(){
    if(x != -1 && y != -1) return true;
    return false;
}


void Mela::Spawn(int x, int y){
    randPos(x,y);
    Utils::initColors();
    wattron(this->win, COLOR_PAIR(3));
    mvwaddch(this->win, y, x, character);
    wattroff(this->win, COLOR_PAIR(3));
}


// Controlla se la posizione della mela e' la stessa della testa del serpente, se true disattiva la mela dalla griglia.
bool Mela::check(Serpente *serp){
    body temp = *serp->getHeadPos();
    if(this->x == temp.x && this->y == temp.y){ 
        return true;
    }
    return false;
}

int Mela::xPos(){
    return x;
}

int Mela::yPos(){
    return y;
}