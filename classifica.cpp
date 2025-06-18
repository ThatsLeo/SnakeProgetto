#pragma once
#include "classifica.h"
#include "utils/utils.h"
#include "file_handler/file_manager.h"
#include <cstring>  

struct ScoreEntry {
    char name[64];
    int score;
};

void sortScores(ScoreEntry* entries, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (entries[j].score < entries[j + 1].score) {
                
                ScoreEntry temp = entries[j];
                entries[j] = entries[j + 1];
                entries[j + 1] = temp;
            }
        }
    }
}

int stringToInt(const char* str) {
    int result = 0;
    int sign = 1;
    int i = 0;
    
    while (str[i] == ' ' || str[i] == '\t') i++;

    if (str[i] == '-') {
        sign = -1;
        i++;
    }

    while (str[i] >= '0' && str[i] <= '9') {
        result = result * 10 + (str[i] - '0');
        i++;
    }
    
    return result * sign;
}

char* findChar(char* str, char ch) {
    while (*str) {
        if (*str == ch) return str;
        str++;
    }
    return nullptr;
}

int getStringLength(const char* str) {
    int len = 0;
    while (str[len]) len++;
    return len;
}

void Classifica::start_classifica() {
    initscr();
    curs_set(0);
    noecho();
    start_color();

    init_pair(1, COLOR_YELLOW, COLOR_BLACK); 
    init_pair(2, COLOR_CYAN, COLOR_BLACK);     
    init_pair(3, COLOR_RED, COLOR_BLACK);  
    init_pair(4, COLOR_WHITE, COLOR_BLACK);    
    init_pair(5, COLOR_WHITE, COLOR_BLACK);    
    
    FileManager fileManager;
    
    const int bufferSize = 2048;
    const int maxEntries = 50;
    char buffer[bufferSize];
    ScoreEntry entries[maxEntries];
    int entryCount = 0;
    
    int charsRead = fileManager.readFile(buffer, bufferSize);
      if (charsRead == 0) {

        mvprintw(10, 10, "Classifica vuota o file non trovato.");
        mvprintw(12, 10, "Premi un tasto per continuare...");
        refresh();
        getch();
        return;
    }
    
    char* line = buffer;
    char* nextLine;
    
    while (line && *line && entryCount < maxEntries) {
        
        nextLine = line;
        while (*nextLine && *nextLine != '\n') nextLine++;
        if (*nextLine == '\n') {
            *nextLine = '\0';
            nextLine++;
        } else {
            nextLine = nullptr;
        }
        
        
        if (getStringLength(line) == 0 || !findChar(line, ':')) {
            line = nextLine;
            continue;
        }
        
        char* colonPos = findChar(line, ':');
        if (colonPos && colonPos != line) {
        
            int nameLen = colonPos - line;
            if (nameLen >= 64) nameLen = 63;
            
            int i;
            for (i = 0; i < nameLen; i++) {
                entries[entryCount].name[i] = line[i];
            }
            entries[entryCount].name[i] = '\0';
            
           
            entries[entryCount].score = stringToInt(colonPos + 1);
            entryCount++;
        }
        
        line = nextLine;
    }
      
    if (entryCount > 0) {
        sortScores(entries, entryCount);
    }
    
    
    int displayCount = entryCount;
    if (displayCount > 10) {
        displayCount = 10;
    }
    
   
    int windowHeight, windowWidth;
    int maxNameLen = 0;
    
   
    for (int i = 0; i < displayCount; i++) {
        int nameLen = getStringLength(entries[i].name);
        if (nameLen > maxNameLen) {
            maxNameLen = nameLen;
        }
    }
      
    windowWidth = 4 + maxNameLen + 2 + 8 + 8; 
    if (windowWidth < 35) windowWidth = 35;
    if (windowWidth > 80) windowWidth = 80;
    
    if (displayCount == 0) {
        windowHeight = 3 + 1 + 3 + 2; 
    } else {
        
        int extraLines = (entryCount > 10) ? 2 : 1; 
        windowHeight = 3 + displayCount + 2 + extraLines + 2; 
    }
    
    int screenHeight, screenWidth;
    getmaxyx(stdscr, screenHeight, screenWidth);
    
    
    int startY = (screenHeight - windowHeight) / 2;
    int startX = 2;
    
    if (startY < 0) startY = 0;
    if (startX < 0) startX = 0;
    if (windowHeight > screenHeight) windowHeight = screenHeight;
    if (windowWidth > screenWidth - 4) windowWidth = screenWidth - 4;
    
    char displayBuffer[bufferSize];
    displayBuffer[0] = '\0';
    
    
    strcat(displayBuffer, "  === CLASSIFICA ===\n\n");
    
    if (displayCount == 0) {
        strcat(displayBuffer, "  Nessun punteggio registrato.\n\n");
    } else {
        char lineBuffer[128];
        for (int i = 0; i < displayCount; i++) {
            
            sprintf(lineBuffer, "  %d. %s: %d\n", i + 1, entries[i].name, entries[i].score);
            strcat(displayBuffer, lineBuffer);
        }
        
        if (entryCount > 10) {
            strcat(displayBuffer, "\n  (Mostrando i primi 10 punteggi)\n");
        }
    }
    
    strcat(displayBuffer, "\n  Premi un tasto per tornare\n  al menu...");  
    WINDOW* classWindow = newwin(windowHeight, windowWidth, startY, startX);
    if (classWindow) {
        
        box(classWindow, 0, 0);
        
        int currentY = 1;
        
        wattron(classWindow, COLOR_PAIR(5));
        mvwprintw(classWindow, currentY++, 2, "=== CLASSIFICA ===");
        wattroff(classWindow, COLOR_PAIR(5));
        currentY++;
        
        if (displayCount == 0) {
            mvwprintw(classWindow, currentY, 2, "Nessun punteggio registrato.");
        } else {
            
            for (int i = 0; i < displayCount; i++) {
                int colorPair;
                if (i == 0) {
                    colorPair = 1; 
                } else if (i == 1) {
                    colorPair = 2; 
                } else if (i == 2) {
                    colorPair = 3; 
                } else {
                    colorPair = 4; 
                }
                
                wattron(classWindow, COLOR_PAIR(colorPair));
                mvwprintw(classWindow, currentY++, 2, "%d. %s: %d", i + 1, entries[i].name, entries[i].score);
                wattroff(classWindow, COLOR_PAIR(colorPair));
            }
            
            if (entryCount > 10) {
                currentY++;
                mvwprintw(classWindow, currentY++, 2, "(Mostrando i primi 10 punteggi)");
            }
        }
        
        
        currentY++;
        mvwprintw(classWindow, currentY++, 2, "Premi un tasto per tornare");
        mvwprintw(classWindow, currentY, 2, "al menu...");
        
        wrefresh(classWindow);
        
        getch();
        
        delwin(classWindow);
    } else {
        
        clear();
        mvprintw(2, 2, "%s", displayBuffer);
        refresh();
        getch();
    }
}