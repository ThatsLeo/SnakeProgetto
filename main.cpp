#include "main.h"

// non scrivete niente nel main.

int main() {
    initialize_ncurses();
    FileManager fileManager = FileManager();
    Menu menu = Menu();

    fileManager.writeFile("Hello World\n");
    fileManager.writeFileAppend("Fra:200 \n");
    fileManager.writeFileAppend("leo:100 \n");
    
    clear();
    refresh();

    menu.start_menu();
    
    std::cout << "Menu chiuso, clicca qualcosa per chiudere" << std::endl;
    int cs = getch();

    return 0;
}