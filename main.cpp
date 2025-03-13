#include "main.h"

int main() {
    Menu menu = Menu();
    menu.start_menu();


    std::cout << "Menu chiuso" << std::endl;
    int c = getch();

    return 0;
}