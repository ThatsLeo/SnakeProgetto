#include "../includes/include.h"


class Menu {
    public:
        Menu();
        ~Menu();
        void initialize_ncurses();
        void print_menu();
        void process_input(int c);
        int handle_user_input();
        void start_menu();
    
    private:
        WINDOW *menu_win;
        int highlight;
        int choice;
        int n_choices;
        const char *choices[4];
    };
    