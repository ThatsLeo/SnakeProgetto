#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "../includes/include.h"
#include "../utils/utils.cpp"
#include "../file_handler/file_manager.cpp"


class Menu {
public:
    Menu();

    ~Menu();

    void close_menu();

    void start_menu();

private:

    void print_menu();   

    void displayTitle();

    void removeTitle();

    void process_input(int c);

    int handle_user_input();

    void gameOver(int game_state);

    WINDOW* menu_win;          
    int highlight;             
    int choice;               
    int old_choice;          
    int n_choices;            
    const char* choices[4];    

    int starty;            
    int startx;             
};

#endif
    