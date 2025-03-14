#include "main.h"
#include "file_handler/file_manager.cpp"
// non scrivete niente nel main.
WINDOW* CreateBoxWindowCentered(WINDOW * boxForFile, int heightDivisor, int widthDivisor) {
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    
    int height = yMax/heightDivisor;
    int width = xMax/widthDivisor;
    int starty = (LINES - height) / 2 + 0;
    int startx = (COLS - width) / 2 + 0; // per centrare la finestra

    // Create the window for the menu
    boxForFile = newwin(height, width, starty, startx);
    refresh();
    box(boxForFile, 0, 0);
    
    return boxForFile;
}



int main() {
    initialize_ncurses();

    writeFile("Hello World\n");
    const int bufferSize = 1024; // massimo 1024 caratteri compreso null-terminator
    char buffer[bufferSize];
    readFile(buffer, bufferSize);
    mvprintw(0, 0, "Press enter to start also this is whats in the save file:\n \n");

    WINDOW * boxForFile;
    boxForFile = CreateBoxWindowCentered(boxForFile, 5, 2); 
    mvwprintw(boxForFile, 2, 3, ("%s", buffer) );
    wrefresh(boxForFile); // refresh window in this case the box 

    refresh(); // refresh the screen(console whole screen i guess idk porcodidddidoooooo)

    getch();
    clear();
    refresh();

    Menu menu = Menu();
    menu.start_menu();
    
    std::cout << "Menu chiuso, clicca qualcosa per chiudere" << std::endl;
    int cs = getch();

    return 0;
}