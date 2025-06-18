#include "Livelli.hpp"
#include "../includes/include.h"
#pragma once

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
    else {
        level::setLevel(1);
    }
}
void level::prevLevel(){
    if (currentlvl->prev != NULL){
        currentlvl = currentlvl->prev;
    }
    else {
        level::setLevel(n_levels);
    }
}
void level::setLevel(int id){
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
    werase(win);         
    level *tmp = head;
    int row = 0;
    
        while (tmp != NULL) {
            if (tmp->id == currentlvl->id) {
                wattron(win, A_REVERSE);  
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
        case (char)10:   
            levelChosen = currentlvl->id; 
            return currentlvl->id;
        case (char)27:  
            return -2;
        default:
            return 0;
    }
    return 0;
}