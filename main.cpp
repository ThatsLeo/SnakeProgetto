#include "main.h"

// non scrivete niente nel main.

int main() {
    initialize_ncurses();
    FileManager fileManager = FileManager();
    Menu menu = Menu();


    fileManager.writeFile("Hello World\n  ORCODIOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO");
    fileManager.writeFileAppend("P O R C O D I O\n");
    
    const int bufferSize = 1024; // massimo 1024 caratteri compreso null-terminator
    char buffer[bufferSize];
    fileManager.readFile(buffer, bufferSize);
    mvprintw(0, 0, "Press enter to start (duicane) also this is whats in the save file:\n \n");

    WINDOW * boxForFile;
    boxForFile = Utils::CreateBoxWindowCentered(boxForFile, 5, 2); 
    mvwprintw(boxForFile, 2, 3, ("%s", buffer) );
    wrefresh(boxForFile); // refresh window in this case the box 

    refresh(); // refresh the screen(console whole screen i guess idk porcodidddidoooooo)

    getch();
    clear();
    refresh();

    menu.start_menu();
    
    std::cout << "Menu chiuso, clicca qualcosa per chiudere" << std::endl;
    int cs = getch();

    return 0;
}