#include "Livelli.hpp"
#include "../includes/include.h"
#pragma once

level::level(){          // Crea una lista bidirezionale di 10 livelli
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
void level::PrintLevels(WINDOW *win){         // Stampa i livelli nel menu
    level *tmp = head;
    int row = 0;
    while (tmp != NULL){
        mvwprintw(win, getmaxy(win) / 2 - n_levels / 2 + row++ , getmaxx(win) / 2 - (9 + std::to_string(tmp->id).length()) / 2, "Livello %d", tmp->id);
        tmp = tmp->next;
    }
    refresh();
}
int level::getId(){
    return currentlvl->id;
}