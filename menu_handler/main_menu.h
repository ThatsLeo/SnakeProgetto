#include "../includes/include.h"
#include "../utils/utils.cpp"
#include "../file_handler/file_manager.cpp"
#pragma once

class Menu {
    public:  // lasciamo usare solo chiudi ed apri menu
        Menu();
        ~Menu();
        void close_menu();
        void start_menu();
    
    private:
        void print_menu();
        void process_input(int c);
        int handle_user_input();

        WINDOW *menu_win;
        int highlight;
        int choice;
        int old_choice;
        int n_choices;
        const char *choices[4];

        int starty;
        int startx; // per centrare la finestra
    };
    