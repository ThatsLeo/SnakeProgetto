#include "main.h"
#include "menu_handler/main_menu.cpp"
#include "gioco/Livelli.cpp"

// non scrivete niente nel main.

int main() {
    initialize_ncurses();
    Menu menu = Menu();

    menu.start_menu();

    return 0;
}
// int main() {
//     initialize_ncurses();
//     clear();
//     refresh();
//     initscr();
//     noecho();
//     cbreak();
//     int yMax, xMax;
//     getmaxyx(stdscr, yMax, xMax);
//     WINDOW *menuwin = newwin(6, xMax-12, yMax-8, 5);
//     box(menuwin, 0, 0);
//     refresh();
//     wrefresh(menuwin);
//     keypad(menuwin, TRUE);
//     std::string choices[10] = level::PrintLevels();
//     int choice;
//     int highlight = 0;
//     while(1){
//         for(int i = 0; i < 10; i++){
//             if(i == highlight){
//                 wattron(menuwin, A_REVERSE);
//                 mvwprintw(menuwin, i+1, 1, choices[i].c_str());
//                 wattroff(menuwin, A_REVERSE);
//             }
//         }
//         choice = wgetch(menuwin);
//         switch(choice){
//             case KEY_UP:
//                 highlight--;
//                 if(highlight == -1) highlight = 0;
//                 break;
//             case KEY_DOWN:
//                 highlight++;
//                 if(highlight == 10) highlight = 9;
//                 break;
//             case 10:
//                 // do something with the selected level
//                 break;
//             default:
//                 break;
//         }
//         if (choice == 10) {
//             break; 
//         }
//         wrefresh(menuwin);
//     }
//}