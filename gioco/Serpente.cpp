#include "../utils/utils.h"
#include "Serpente.hpp"

// Costruttore base del serpente(finestra di stampa, coordinate di inizio e carattere di stampa).
Serpente::Serpente(WINDOW * win, char c, int lenght){
    
    this->win = win; 
    character = c;
    head = new body{Maxx/2, Maxy/2, nullptr};
    headX = Maxx/2;
    headY = Maxy/2;
    
    dir = UP;
    
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

void Serpente::moveBy(int dx, int dy) {
    headX += dx;
    headY += dy;
    
    if (headX < 1) {
        headX = Maxx - 2;
    } else if (headX > Maxx - 2) {
        headX = 1;
    }
    
    if (headY < 1) {
        headY = Maxy - 2;
    } else if (headY > Maxy - 2) {
        headY = 1;
    }
    
    head = addBody(headY, headX);
    body *delTail = tail();
    body *newTail = prevTail();
    delete delTail;
    newTail->next = nullptr;
}

void Serpente::moveUp(){
    moveBy(0, -1);
}

void Serpente::moveDown(){
    moveBy(0, 1);
}

void Serpente::moveLeft(){
    moveBy(-1, 0);
}

void Serpente::moveRight(){
    moveBy(1, 0);
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


static Direction getDesiredDirection(int key, Direction current) {
    struct Mapping {
        int key;
        Direction newDir;
        Direction opposite;
    };

    static const Mapping mappings[] = {
        { KEY_UP,    UP,    DOWN },
        { KEY_DOWN,  DOWN,  UP },
        { KEY_LEFT,  LEFT,  RIGHT },
        { KEY_RIGHT, RIGHT, LEFT }
    };

    for (const auto& m : mappings) {
        if (m.key == key) {
            return (current == m.opposite) ? current : m.newDir;
        }
    }
    return current;
}

static void performMove(Serpente* self, Direction newDir) {
    switch(newDir) {
        case UP:
            self->moveUp();
            break;
        case DOWN:
            self->moveDown();
            break;
        case LEFT:
            self->moveLeft();
            break;
        case RIGHT:
            self->moveRight();
            break;
        default:
            break;
    }
}

// Refactored updateDirection: it tries to update the direction based on key press,
// and if a valid change is found it updates the state and performs the proper move.
static bool updateDirection(Serpente* self, int key) {
    Direction desiredDir = getDesiredDirection(key, self->dir);
    if (desiredDir != self->dir) {
        self->blank();
        self->dir = desiredDir;
        performMove(self, desiredDir);
        return true;
    }
    return false;
}


void Serpente::setMove(int key) {
    
    Direction desiredDir = getDesiredDirection(key, this->dir);
    if (desiredDir != this->dir) {
        this->dir = desiredDir;
    }
}

// Aggiorna le coordinate del serpente sulla matrice del display
void Serpente::display(){
    body *current = head;
    Utils::initColors();
    wattron(win, COLOR_PAIR(1));
    mvwaddch(win, headY, headX, '@');  // Testa = '@'
    wattroff(win, COLOR_PAIR(1));

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


bool Serpente::firstMove(){
    body *corpo = head->next;
    while(corpo != nullptr){
        if(headX != corpo->x || headY != corpo->y) return false;
        corpo = corpo->next;
    }
    return true;
}

bool Serpente::autoCollision() {
    body *corpo = head->next;
    while (corpo != nullptr) {
        if (headX == corpo->x && headY == corpo->y) {
            Utils::wait(400); // Pause for 1 second before returning true
            return true;
        }
        corpo = corpo->next;
    }
    return false;
}