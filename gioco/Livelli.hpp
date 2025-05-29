#pragma once
class level{        // Classe per la gestione dei livelli
private:
    int id;         // Identificatore del livello
    level *next;
    level *prev;
    level *currentlvl;
    level *head;
    level *tail;
public:
    level();
    level(int id, level *next, level *prev){
        this->id = id;
        this->next = next;
        this->prev = prev;
    }
    void nextLevel();       // Metodi per scorrere la lista
    void prevLevel();
    void setLevel(int id);
    void PrintLevels();     // Funzione per stampare i livelli nel menu
    int getId();
};