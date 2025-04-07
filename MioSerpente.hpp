#include "includes/include.h"
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
        Serpente(WINDOW * win, char c, int lenght);

        body *getHeadPos();

        inline void wait(int milliseconds);

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
        
        void display();

        Direction getDir();

    private:
        Direction dir;
        int headX, headY;
        body *head;
        char character;
        WINDOW * win;
};
// Costruttore base del serpente(finestra di stampa, coordinate di inizio e carattere di stampa).
Serpente::Serpente(WINDOW * win, char c, int lenght){
    
    this->win = win; 
    character = c;
    head = new body{Maxx/2, Maxy/2, nullptr};
    headX = Maxx/2;
    headY = Maxy/2;
    body* current = head;
    // Il serpente ha inizialmente ogni pezzo alle stesse coordinate.
    for (int i = 1; i < lenght; i++) {
        body* newbody = new body{Maxy/2, Maxx/2, nullptr};
        current->next = newbody;
        current = newbody;
    }

    keypad(this->win, true);
    character = c;
}

// Movimento in alto.
void Serpente::moveUp(){ 
    headY -= 1; 
    
    if(headY < 1){
        headY = Maxy-2;
    }
    
    head = addBody(headY, headX);
    body *delTail = tail();
    body *newTail = prevTail();
    delete delTail;
    newTail->next = nullptr;
}

// Movimento in basso.
void Serpente::moveDown(){
    headY += 1; 
    
    if(headY > Maxy-2){
        headY = 1;
    }
    
    head = addBody(headY, headX);
    body *delTail = tail();
    body *newTail = prevTail();
    delete delTail;
    newTail->next = nullptr;
}

// Movimento a sinistra.
void Serpente::moveLeft(){
    headX -= 1; 
    
    if(headX < 1){
        headX = Maxx-2;
    }
    
    head = addBody(headY, headX);
    body *delTail = tail();
    body *newTail = prevTail();
    delete delTail;
    newTail->next = nullptr;
}

// Movimento a destra.
void Serpente::moveRight(){
    headX += 1; 
    
    if(headX > Maxx-2){
        headX = 1;
    }
    
    head = addBody(headY, headX);
    body *delTail = tail();
    body *newTail = prevTail();
    delete delTail;
    newTail->next = nullptr;
}


void Serpente::defaultMove(){
    switch(dir){
        case UP:
            blank();
            moveUp();
            break;
        
        case DOWN:
            blank();
            moveDown();
            break;

        case LEFT:
            blank();    
            moveLeft();
            break;

        case RIGHT:
            blank();
            moveRight();
            break;
        default:
            break;
        
    }
}



// Funzione che prende da tastiera (KEY UP, KEY DOWN, KEY LEFT, KEY RIGHT).
int Serpente::getMove(){
    int moveKey = wgetch(this->win);
    switch(moveKey){
        case KEY_UP:
            if(dir == DOWN || dir == UP) break;
            blank();
            dir = UP;
            moveUp();
            break;

        case KEY_DOWN:
            if(dir == UP || dir == DOWN) break;
            blank();
            dir = DOWN;
            moveDown();
            break;

        case KEY_LEFT:
            if(dir == RIGHT || dir == LEFT) break;
            blank();
            dir = LEFT;
            moveLeft();
            break;

        case KEY_RIGHT:
            if(dir == LEFT || dir == RIGHT) break;
            blank();
            dir = RIGHT;
            moveRight();
            break;
        
        default:
            wait(160); 
            defaultMove();
            break;
    }

    return dir;
}

// Aggiorna le coordinate del serpente sulla matrice del display
void Serpente::display(){
    body *current = head;
    mvwaddch(win, headY, headX, '@');  // Testa = '@'
    current = current->next;

    // Corpo
    while(current != nullptr) {
            mvwaddch(win, current->y, current->x, character); 
            current = current->next;
    }
}

// Ritorna un puntatore al blocco precedente alla coda.
body *Serpente::prevTail(){
    body *temp = head;
    while(temp->next != nullptr && temp->next->next != nullptr){
        temp = temp->next;
    }
    return temp;
}

// Ritorna un puntatore alla coda del serpente
body* Serpente::tail(){
    body *temp = head;
    while(temp->next != nullptr){
        temp = temp->next;
    }
    return temp;
}

// Aggiunge un blocco in testa al serpente. 
body * Serpente::addBody(int y, int x){
    body *temp = new body{y, x, nullptr};
    temp->next = head;
    return temp;
}

// Sovrascrive un carattere nel display con uno spazio vuoto(ci elimino la vecchia coda).
void Serpente::blank(){
    body *tempTail = tail();
    mvwaddch(win, tempTail->y, tempTail->x, ' ');
}

// Ritorna la struttura della testa del serpente.
body *Serpente::getHeadPos(){
    body *temp = head;
    return temp;
}

// Una funzione sleep() in millisecondi con ctime.
inline void Serpente::wait(int milliseconds){
    clock_t start_time = clock();
    clock_t end_time = start_time + milliseconds * CLOCKS_PER_SEC / 1000;

    while (clock() < end_time) {
        
    }
}

Direction Serpente::getDir(){
    return dir;
}

