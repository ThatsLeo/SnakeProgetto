class level{        // Classe per la gestione dei livelli
private:
    struct level{
        int id;
        level *next;
        level *prev;
    };
    level *currentlvl;
    level *head;
    level *tail;

public:
    level();
    void nextLevel();       // Metodi per scorrere la lista
    void prevLevel();
    void setLevel(int id);
}