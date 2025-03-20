
#include "main.h"
#include "menu_handler/main_menu.cpp"
#include "file_handler/file_manager.cpp"

// non scrivete niente nel main.

int main() {
    initialize_ncurses();
    FileManager fileManager = FileManager();
    Menu menu = Menu();

    fileManager.writeFile("Classifica\n");
    fileManager.writeFileAppend("Fra:200 \n");
    fileManager.writeFileAppend("leo:100 \n");
    
    clear();
    refresh();

    menu.start_menu();
    
    std::cout << "Menu chiuso, clicca qualcosa per chiudere" << std::endl;
    int cs = getch();

    return 0;
}