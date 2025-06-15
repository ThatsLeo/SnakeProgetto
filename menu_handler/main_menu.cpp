#include "main_menu.h"
#include "../gioco/game.cpp"
#include "../classifica.cpp"
#include "../gioco/Livelli.cpp"
#include <cstring>  


char playerName[32] = "Guest";    
WINDOW* titleWin = nullptr;

void getPlayerName()
{
    int nameWinHeight = 6;
    int nameWinWidth = 40;
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    int nameStartY = (yMax - nameWinHeight) / 2;
    int nameStartX = (xMax - nameWinWidth) / 2;

    WINDOW *nameWin = newwin(nameWinHeight, nameWinWidth, nameStartY, nameStartX);
    keypad(nameWin, TRUE);

    clear();
    refresh();
    box(nameWin, 0, 0);

    noecho();    
    curs_set(1); 

    
    char tempName[32] = ""; 
    int nameIndex = 0;     

    mvwprintw(nameWin, 1, 2, "Inserisci il tuo nome:");
    mvwprintw(nameWin, 2, 2, "> ");
    wrefresh(nameWin); 

    wmove(nameWin, 2, 4); 

    int c;
    while ((c = wgetch(nameWin)))
    {
        if (c == 10 || c == 13 || c == KEY_ENTER) break;
    
        else if (c == KEY_BACKSPACE || c == 127 || c == 8){ 
            if (nameIndex > 0){
                nameIndex--;
                tempName[nameIndex] = '\0';
                
                int curX = getcurx(nameWin);
                if (curX > 4){
                    mvwprintw(nameWin, 2, curX - 1, " ");
                    wmove(nameWin, 2, curX - 1);
                    wrefresh(nameWin);
                }
            }
        }
        else if (c >= 32 && c <= 126 && nameIndex < 30){ 
            tempName[nameIndex] = c;
            tempName[nameIndex + 1] = '\0';
            nameIndex++;
            
            wprintw(nameWin, "%c", c);
            wrefresh(nameWin);
        }
        
        else if (c == KEY_LEFT){
            int curX = getcurx(nameWin);
            if (curX > 4){
                wmove(nameWin, 2, curX - 1);
            }
        }
        else if (c == KEY_RIGHT){
            int curX = getcurx(nameWin);
            if (curX < 4 + nameIndex && curX < nameWinWidth - 2)
            {
                wmove(nameWin, 2, curX + 1);
            }
        }

        wrefresh(nameWin);
    }
    
    strncpy(playerName, tempName, 31);
    playerName[31] = '\0'; 

    if (strlen(playerName) == 0)
    {
        strcpy(playerName, "Guest");
    }

    curs_set(0); 
    
    delwin(nameWin);
    clear();
    refresh();
}

Menu::Menu() 
    : highlight(1), choice(0), n_choices(4), old_choice(0) {
    choices[0] = "Gioca";
    choices[1] = "Classifica";
    choices[2] = "Livelli";
    choices[3] = "Esci";

    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    
    int height = yMax/2;
    int width = xMax/3;
    starty = (LINES - height) / 2;
    startx = (COLS - width) / 2; 

    menu_win = newwin(height, width, starty, startx);
    keypad(menu_win, TRUE);
    refresh();
}

Menu::~Menu() {
    delwin(menu_win);
}

void SalvaPunteggio(int score) {
    if(score <= 0) return; 
    
    FileManager fileManager = FileManager();
    char scoreEntry[100];
    sprintf(scoreEntry, "%s:%d \n", playerName, score);
    fileManager.writeFileAppend(scoreEntry);
}

void Menu::gameOver(int game_state) {
    if(game_state == GAME_OVER_COLLISION) {
    
        Utils::wait(200);
        SalvaPunteggio(punteggioFinale);
        mvprintw(2, startx + 3, "Game Over\n");
        mvprintw(3, startx + 3, "Press esc to return to menu\n");
        refresh();
        int c;
            while(c = wgetch(menu_win)){
                if (c == (char)27 || c == (char)10) break;
            }
    } 
    else if(game_state == BYPASSGAMEOVER) {
        
        SalvaPunteggio(punteggioFinale);
    } 
    else {
        
        mvprintw(0, startx, "Game Over\n");
        mvprintw(1, startx, "New Record!\n");
        mvprintw(2, startx, "Press esc to return to menu\n");        
        SalvaPunteggio(game_state);
    }
}


void Menu::displayTitle() {
    
    int titleHeight = 7;
    int titleWidth = 38;
    
    int titleStartY = 0; 
    int titleStartX = (COLS - titleWidth) / 2; 
    
    if (titleWin != nullptr) {
        delwin(titleWin);
    }
    
    titleWin = newwin(titleHeight, titleWidth, titleStartY, titleStartX);
    box(titleWin, 0, 0);
    Utils::initColors();
    wattron(titleWin, COLOR_PAIR(4));
    mvwprintw(titleWin, 1, 2, " SSS   S  S   SSSSS   S  S   SSSSS");
    mvwprintw(titleWin, 2, 2, "S      SS S   S   S   S S    S    ");
    mvwprintw(titleWin, 3, 2, " SSS   S SS   SSSSS   SS     SSSS ");
    mvwprintw(titleWin, 4, 2, "    S  S  S   S   S   S S    S    ");
    mvwprintw(titleWin, 5, 2, " SSS   S  S   S   S   S  S   SSSSS");
    wattroff(titleWin, COLOR_PAIR(4));
    
    wrefresh(titleWin);
}

void Menu::removeTitle() {
    if (titleWin != nullptr) {
        wclear(titleWin);
        wrefresh(titleWin);
        delwin(titleWin);
        titleWin = nullptr;
    }
    clear();
    refresh();
}

void Menu::print_menu() {
    box(menu_win, 0, 0);
    
    for(int i = 0; i < n_choices; ++i) {
        int x = getmaxx(menu_win) /2 - std::strlen(choices[i]) / 2;
        int y = getmaxy(menu_win)/ 2 + i - n_choices /2;
        
        if(highlight == i + 1) { 
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", choices[i]);
            wattroff(menu_win, A_REVERSE); 
        } else {
            mvwprintw(menu_win, y, x, "%s", choices[i]);
        }
    }
    wrefresh(menu_win);
}

void Menu::process_input(int c) {
    switch(c) {
        case KEY_UP:
            highlight--;
            if(highlight < 1)
                highlight = n_choices;
            break;
        case KEY_DOWN:
            highlight++;
            if(highlight > n_choices)
                highlight = 1;
            break;
        case 10: 
            choice = highlight;
            break;
        default:
            break;
    }
}

int Menu::handle_user_input() {
    int c;
    displayTitle();
    print_menu();
    while(1) {
        c = wgetch(menu_win);
        process_input(c);
        displayTitle();
        print_menu();
        if(choice != 0) 
            break;
    }
    return choice;
}
level levelMenu;
bool pressed_exit = 0;
int game_state;

void Menu::start_menu() {
    
    getPlayerName();
    
    FileManager fileManager = FileManager();

    fileManager.writeFile("Classifica\n");
    
    while (true) {
        curs_set(0); 
        noecho(); 
        highlight = old_choice; 
        choice = 0;
        clear(); 
        refresh(); 
        wclear(menu_win); 
        wrefresh(menu_win);        
        int choice = handle_user_input(); 
        old_choice = choice; 
        
        if (choice == 1) {   
            removeTitle();
            game_state = start_game();
            gameOver(game_state);
            
        }else if (choice == 2) {
             
            Utils::initColors();
            Classifica::start_classifica();
        }else if (choice == 3){
            
            wclear(menu_win);
            wrefresh(menu_win);
            WINDOW * insideBox;
            insideBox = Utils::CreateBoxWindowCentered(insideBox, 2, 4); 
            keypad(insideBox, TRUE);
            while(true){
                levelMenu.PrintLevels(insideBox);
                int c = levelMenu.processInput(wgetch(insideBox));
                if (c > 0){
                    removeTitle();
                    game_state = start_game();
                    gameOver(game_state);
                    break;
                }
                else if (c == -2){
                    break;
                }   
        }
            wrefresh(insideBox);
            refresh();
        }
         else if (choice == 4) {
            break;
        }

        clrtoeol();
        
        refresh();
    }
    
}
