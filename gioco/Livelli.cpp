#include "Livelli.hpp"
#include "../includes/include.h"
#pragma once
// Crea una lista bidirezionale di 10 livelli


level::level(int id, level* next, level* prev){
        this->id = id;
        this->next = next;
        this->prev = prev;
    }

level::level(){          
    n_levels = 10;

    head = new level{1, NULL, NULL};
    level *tmphead = head;
    currentlvl = head;
    for (int i = 2; i <= n_levels; i++){
        level *tmp = new level{i, NULL, tmphead};
        tmphead->next = tmp;
        tmphead = tmp;
    }
    tail = tmphead;
}
void level::nextLevel(){
    if (currentlvl->next != NULL){
        currentlvl = currentlvl->next;
    }
}
void level::prevLevel(){
    if (currentlvl->prev != NULL){
        currentlvl = currentlvl->prev;
    }
}
void level::setLevel(int id){         // Cerca il livello con id specificato e lo imposta come currentlvl
    level *tmp = head;              
    while (tmp != NULL){
        if (tmp->id == id){
            currentlvl = tmp;
            return;
        }
        tmp = tmp->next;
    }
}
void level::PrintLevels(WINDOW *win){
    werase(win);         // Stampa i livelli nel menu
    level *tmp = head;
    int row = 0;
    // Stampa tutti i livelli, evidenziando quello selezionato
        while (tmp != NULL) {
            if (tmp->id == currentlvl->id) {
                wattron(win, A_REVERSE);  // Evidenzia il livello selezionato
                mvwprintw(win, getmaxy(win) / 2 - n_levels / 2 + row,
                         getmaxx(win) / 2 - (9 + std::to_string(tmp->id).length()) / 2,
                         "Livello %d", tmp->id);
                wattroff(win, A_REVERSE);
            } else {
                mvwprintw(win, getmaxy(win) / 2 - n_levels / 2 + row,
                         getmaxx(win) / 2 - (9 + std::to_string(tmp->id).length()) / 2,
                         "Livello %d", tmp->id);
            }
            row++;
            tmp = tmp->next;
        }
        box(win, 0, 0);
        wrefresh(win);
}
int level::getId(){
    return currentlvl->id;
}

int level::processInput(int c) {

    switch(c) {
        case KEY_UP:
            prevLevel();
            return 0;
        case KEY_DOWN:
            nextLevel();
            return 0;
        case (char)10:  // Enter 
            levelChosen = currentlvl->id;  // Imposta il livello scelto
            return currentlvl->id;
        case (char)27:  // ESC
            return -2;
        default:
            return 0;
    }
    return 0;
}