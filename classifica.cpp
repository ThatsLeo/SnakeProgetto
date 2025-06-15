#pragma once
#include "classifica.h"
#include "utils/utils.h"
#include "file_handler/file_manager.h"
#include <cstring>  

struct ScoreEntry {
    char name[64];
    int score;
};

// bubble sort per la classifica
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

// da punteggio in caratteri ad intero
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

    init_pair(1, COLOR_YELLOW, COLOR_BLACK); // Gold primo posto
    init_pair(2, COLOR_CYAN, COLOR_BLACK);   // Silver secondo posto  
    init_pair(3, COLOR_RED, COLOR_BLACK);    // Bronze terzo posto
    init_pair(4, COLOR_WHITE, COLOR_BLACK);    
    init_pair(5, COLOR_WHITE, COLOR_BLACK);    
    
    FileManager fileManager;
    
    const int bufferSize = 2048;
    const int maxEntries = 50;
    char buffer[bufferSize];
    ScoreEntry entries[maxEntries];
    int entryCount = 0;
    
    // Read the file
    int charsRead = fileManager.readFile(buffer, bufferSize);
      if (charsRead == 0) {
        // Empty file or error
        mvprintw(10, 10, "Classifica vuota o file non trovato.");
        mvprintw(12, 10, "Premi un tasto per continuare...");
        refresh();
        getch();
        return;
    }
    
    // Parse the file content line by line
    char* line = buffer;
    char* nextLine;
    
    while (line && *line && entryCount < maxEntries) {
        // Find next line
        nextLine = line;
        while (*nextLine && *nextLine != '\n') nextLine++;
        if (*nextLine == '\n') {
            *nextLine = '\0';
            nextLine++;
        } else {
            nextLine = nullptr;
        }
        
        // Skip empty lines and header
        if (getStringLength(line) == 0 || !findChar(line, ':')) {
            line = nextLine;
            continue;
        }
        
        // Find the colon separator
        char* colonPos = findChar(line, ':');
        if (colonPos && colonPos != line) {
            // Extract name (everything before colon)
            int nameLen = colonPos - line;
            if (nameLen >= 64) nameLen = 63;
            
            int i;
            for (i = 0; i < nameLen; i++) {
                entries[entryCount].name[i] = line[i];
            }
            entries[entryCount].name[i] = '\0';
            
            // Extract score (everything after colon)
            entries[entryCount].score = stringToInt(colonPos + 1);
            entryCount++;
        }
        
        line = nextLine;
    }
      // Sort entries by score (descending)
    if (entryCount > 0) {
        sortScores(entries, entryCount);
    }
    
    // Determine how many entries to display (max 10)
    int displayCount = entryCount;
    if (displayCount > 10) {
        displayCount = 10;
    }
    
    // Calculate window dimensions based on content
    int windowHeight, windowWidth;
    int maxNameLen = 0;
    
    // Find the longest name for width calculation
    for (int i = 0; i < displayCount; i++) {
        int nameLen = getStringLength(entries[i].name);
        if (nameLen > maxNameLen) {
            maxNameLen = nameLen;
        }
    }
      // Calculate window size - make it wider to ensure text fits
    // Width: "10. " + max_name_length + ": " + max_score_digits + extra padding
    // Assuming max score is 6 digits, plus generous padding
    windowWidth = 4 + maxNameLen + 2 + 8 + 8; // "10. name: 999999" + extra padding
    if (windowWidth < 35) windowWidth = 35; // Increased minimum width for header
    if (windowWidth > 80) windowWidth = 80; // Increased maximum width for better display
    
    // Height: header (3 lines) + entries + footer lines + borders (2)
    if (displayCount == 0) {
        windowHeight = 3 + 1 + 3 + 2; // Header + "No scores" + footer + borders
    } else {
        // Add extra height for potential overflow message and more spacing
        int extraLines = (entryCount > 10) ? 2 : 1; // Extra line for overflow message
        windowHeight = 3 + displayCount + 2 + extraLines + 2; // Header + entries + footer + borders
    }
    
    // Get screen dimensions for positioning
    int screenHeight, screenWidth;
    getmaxyx(stdscr, screenHeight, screenWidth);
    
    // Position window on the left side of the screen
    int startY = (screenHeight - windowHeight) / 2;
    int startX = 2; // Fixed position on the left with small margin
    
    // Ensure window fits on screen
    if (startY < 0) startY = 0;
    if (startX < 0) startX = 0;
    if (windowHeight > screenHeight) windowHeight = screenHeight;
    if (windowWidth > screenWidth - 4) windowWidth = screenWidth - 4; // Leave margin on right
      // Create display buffer
    char displayBuffer[bufferSize];
    displayBuffer[0] = '\0';
    
    // Add header with better spacing
    strcat(displayBuffer, "  === CLASSIFICA ===\n\n");
    
    if (displayCount == 0) {
        strcat(displayBuffer, "  Nessun punteggio registrato.\n\n");
    } else {
        char lineBuffer[128];
        for (int i = 0; i < displayCount; i++) {
            // Create formatted line with better spacing: "  Position. Name: Score"
            sprintf(lineBuffer, "  %d. %s: %d\n", i + 1, entries[i].name, entries[i].score);
            strcat(displayBuffer, lineBuffer);
        }
        
        // Add note if there are more than 10 entries
        if (entryCount > 10) {
            strcat(displayBuffer, "\n  (Mostrando i primi 10 punteggi)\n");
        }
    }
    
    strcat(displayBuffer, "\n  Premi un tasto per tornare\n  al menu...");    // Create dynamic window
    WINDOW* classWindow = newwin(windowHeight, windowWidth, startY, startX);
    if (classWindow) {
        // Draw border
        box(classWindow, 0, 0);
        
        // Display content with colors manually instead of using InlinedTextWindow
        int currentY = 1;
        
        // Display header with cyan color
        wattron(classWindow, COLOR_PAIR(5));
        mvwprintw(classWindow, currentY++, 2, "=== CLASSIFICA ===");
        wattroff(classWindow, COLOR_PAIR(5));
        currentY++; // Empty line
        
        if (displayCount == 0) {
            mvwprintw(classWindow, currentY, 2, "Nessun punteggio registrato.");
        } else {
            // Display each entry with appropriate color
            for (int i = 0; i < displayCount; i++) {
                int colorPair;
                if (i == 0) {
                    colorPair = 1; // Gold for 1st place
                } else if (i == 1) {
                    colorPair = 2; // Silver for 2nd place
                } else if (i == 2) {
                    colorPair = 3; // Bronze for 3rd place
                } else {
                    colorPair = 4; // Green for other entries
                }
                
                wattron(classWindow, COLOR_PAIR(colorPair));
                mvwprintw(classWindow, currentY++, 2, "%d. %s: %d", i + 1, entries[i].name, entries[i].score);
                wattroff(classWindow, COLOR_PAIR(colorPair));
            }
            
            // Add note if there are more than 10 entries
            if (entryCount > 10) {
                currentY++;
                mvwprintw(classWindow, currentY++, 2, "(Mostrando i primi 10 punteggi)");
            }
        }
        
        // Add footer
        currentY++;
        mvwprintw(classWindow, currentY++, 2, "Premi un tasto per tornare");
        mvwprintw(classWindow, currentY, 2, "al menu...");
        
        wrefresh(classWindow);
        
        // Wait for user input
        getch();
        
        // Clean up
        delwin(classWindow);
    } else {
        // Fallback display - also positioned on the left
        clear();
        mvprintw(2, 2, "%s", displayBuffer);
        refresh();
        getch();
    }
}