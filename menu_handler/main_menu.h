#include "../includes/include.h"


class Menu {
    public:  // lasciamo usare solo chiudi ed apri menu
        Menu();
        ~Menu();
        void close_menu();
        void start_menu();

        //void initialize_ncurses();
    
    private:
        void print_menu();
        void process_input(int c);
        int handle_user_input();

        WINDOW *menu_win;
        int highlight;
        int choice;
        int n_choices;
        const char *choices[4];
    };
    