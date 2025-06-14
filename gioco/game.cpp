#pragma once
#include "Serpente.cpp"
#include "Mela.cpp"
#include "Livelli.cpp"
#include <cstring>

// ========== CONSTANTS AND GLOBALS ==========
#define ESC_KEY 27
#define ENTER_KEY 10
#define GAME_OVER_COLLISION 0

// Window dimensions for game wrapper
int wrapY = Maxy + 2;
int wrapX = Maxx + 3;

// Game state variables
int tempoPassato = 0;  // Time elapsed in seconds
int scoreSnake = 0;    // Current game score

// ========== FUNCTION DECLARATIONS ==========
bool showPauseMenu(WINDOW* gameWin);

// ========== GAME INITIALIZATION FUNCTIONS ==========

// Initialize all game objects (snake, apple, level)
void initializeGame(WINDOW* win, Serpente*& serpent, Mela*& frutto, level*& livello) {
    serpent = new Serpente(win, 'o', 9);
    frutto = new Mela(win, -1, -1, '$');
    livello = new level();
    livello->setLevel(levelChosen);
}

// ========== DISPLAY FUNCTIONS ==========

// Display current score in the wrapper window
void displayScore(WINDOW* win) {
    mvwprintw(win, wrapY - 1, 2, "Punteggio: %d", scoreSnake);
    wrefresh(win);
}

// Display elapsed time in the wrapper window
void displayTime(WINDOW* win) {
    mvwprintw(win, wrapY - 1, wrapX - 15, "Tempo: %d", tempoPassato);
    wrefresh(win);
}

// Display current level in the wrapper window
void displayLevel(WINDOW *win, level* livello) {
    mvwprintw(win, 0, 2, "Livello: %d", levelChosen);
    wrefresh(win);
}

// Show initial game start message
void displayStartMessage(WINDOW* win) {
    mvwprintw(win, 1, 10, "Press something to start..");
    wrefresh(win);
}

// ========== UTILITY FUNCTIONS ==========

// Check if a cell at given coordinates is empty (contains a space)
bool isCellEmpty(WINDOW* win, int y, int x) {
    chtype ch = mvwinch(win, y, x);
    char currentChar = ch & A_CHARTEXT;
    return (currentChar == ' ');
}

// Spawn fruit at a random empty position within game boundaries
void spawnFruit(WINDOW* win, Mela* frutto, int &fruitX, int &fruitY) {
    // Generate random coordinates within game boundaries
    fruitX = (rand() % (Maxx - 3)) + 1;
    fruitY = (rand() % (Maxy - 3)) + 1;
    
    // Keep generating new coordinates until we find an empty cell
    while (!isCellEmpty(win, fruitY, fruitX)) {
        fruitX = rand() % (Maxx - 3) + 1;
        fruitY = (rand() % (Maxy - 3)) + 1;
    }
    
    frutto->Spawn(fruitX, fruitY);
}

// Create and setup game windows (main game window and info wrapper)
void setupGameWindows(WINDOW*& win, WINDOW*& wrap, int& xMax, int& yMax) {
    getmaxyx(stdscr, yMax, xMax);
    
    // Create main game window (centered)
    win = newwin(Maxy, Maxx, yMax/2 - Maxy/2, xMax/2 - Maxx/2);
    
    // Create wrapper window for score/time display (slightly larger, centered)
    wrap = newwin(wrapY, wrapX, yMax/2 - Maxy/2 - 1, xMax/2 - Maxx/2 - 1);
    
    wrefresh(wrap);
    box(win, 0, 0);
}

// ========== GAME INPUT AND LOGIC FUNCTIONS ==========

// Handle initial game start - show message and wait for first key
bool handleGameStart(WINDOW* win) {
    displayStartMessage(win);
    int firstKey = wgetch(win);
    if (firstKey == ESC_KEY) {
        return !showPauseMenu(win);
    }
    return false;
}

// Process user input during gameplay
// Returns true if player wants to exit game, false otherwise
bool processUserInput(WINDOW* win, WINDOW* wrap, Serpente* serpent, 
                     int moveDelay, clock_t& lastMoveCheck, clock_t now) {
    // Check if enough time has passed for next move
    if (now - lastMoveCheck < moveDelay) return false;
    
    // Get the most recent key press (ignore buffered input)
    int lastKey = ERR;
    int key;
    while ((key = wgetch(win)) != ERR) {
        lastKey = key;
    }
    
    // Handle ESC key - show pause menu
    if (lastKey == ESC_KEY) {
        bool shouldResume = showPauseMenu(win);
        if (!shouldResume) {
            return true; // Player chose to exit
        }
    } 
    // Handle other keys - update snake direction
    else if (lastKey != ERR) {
        serpent->setMove(lastKey);
    }
    
    // Move snake and update timing
    serpent->move();
    lastMoveCheck = now;
    return false;
}

// Handle fruit collision and spawning logic
void handleFruitLogic(WINDOW* win, Mela* frutto, Serpente* serpent, int& fruitX, int& fruitY, 
                     clock_t& lastAppleCheck, clock_t now, int appleDelay, int bonusPoints) {
    // Check if snake ate the fruit
    if (frutto->check(serpent)) {
        // Clear the fruit from screen
        mvwaddch(win, frutto->yPos(), frutto->xPos(), ' ');
        lastAppleCheck = clock();
        frutto->off();
        scoreSnake += bonusPoints;
    }
    
    // Spawn new fruit if enough time has passed and no fruit is active
    if (!frutto->isOn() && now - lastAppleCheck >= appleDelay) {
        spawnFruit(win, frutto, fruitX, fruitY);
    }
}

// Check if level is completed and handle completion screen
bool checkLevelCompletion(WINDOW* win, int levelDelay, int bonusPoints) {
    if (tempoPassato >= levelDelay) {
        werase(win);
        box(win, 0, 0);
        mvwprintw(win, Maxy/2, Maxx/2 - 10, "Level Completed!");
        mvwprintw(win, Maxy/2 + 1, Maxx/2 - 10, "Bonus: %d", bonusPoints);
        scoreSnake += bonusPoints;
        wrefresh(win);
        getch();
        return true;
    }
    return false;
}

// ========== MAIN GAME FUNCTION ==========

// Main game loop - handles initialization, gameplay, and cleanup
// Returns: 0 = game over by collision, BYPASSGAMEOVER = exit via menu/level complete
int start_game() {
    // Initialize random seed and ncurses
    srand(time(NULL));
    initscr();
    curs_set(0);  // Hide cursor
    noecho();     // Don't echo input
    
    // Reset game state
    scoreSnake = 0;
    tempoPassato = 0;
    int xMax, yMax, fruitX, fruitY;

    // Create game windows
    WINDOW *win, *wrap;
    setupGameWindows(win, wrap, xMax, yMax);

    // Initialize game objects
    Serpente *serpent;
    Mela *frutto;
    level *livello;
    initializeGame(win, serpent, frutto, livello);

    // Game timing variables
    clock_t lastAppleCheck = clock();
    clock_t lastMoveCheck = clock();
    clock_t lastTime = clock();
    
    // Game configuration
    int appleDelay = CLOCKS_PER_SEC;  // 1 second between apple spawns
    double moveDelay = CLOCKS_PER_SEC / (7.0 + (levelChosen - 1) * 0.666);  // Snake speed
    int levelDelay = 10;  // Level duration in seconds
    int bonusPoints = 100 * livello->getId();  // Points per apple/level
    
    // Show start message and handle initial input
    displayStartMessage(win);
    int firstKey = wgetch(win);
    if (firstKey == ESC_KEY) {  // ESC pressed at start - show pause menu
        bool shouldResume = showPauseMenu(win);
        if (!shouldResume) {
            // Player chose to exit - cleanup and return
            delwin(win);
            delwin(wrap);
            return BYPASSGAMEOVER;
        }
    }

    // Setup for main game loop
    lastTime = clock();
    lastMoveCheck = clock();
    
    // Configure input handling for responsive gameplay
    flushinp();          // Clear input buffer
    nodelay(win, TRUE);  // Enable non-blocking input
    
    // Clear start message
    mvwprintw(win, 1, 10, "                          ");
    wrefresh(win);

    // Game state flags
    bool gameOver = false;
    // ========== MAIN GAME LOOP ==========
    while (true) {
        punteggioFinale = scoreSnake;  // Update global score for saving
        clock_t now = clock();

        // === INPUT HANDLING ===
        if (processUserInput(win, wrap, serpent, moveDelay, lastMoveCheck, now)) {
            // Player chose to exit from pause menu - cleanup and return
            delwin(win);
            delwin(wrap);
            return BYPASSGAMEOVER;
        }

        // === TIME UPDATE ===
        if (now - lastTime >= CLOCKS_PER_SEC) {
            tempoPassato++;  // Increment elapsed time every second
            lastTime = now;
        }

        // === DISPLAY UPDATES ===
        displayScore(wrap);   // Show current score
        displayTime(wrap);    // Show elapsed time
        displayLevel(wrap, livello);  // Show current level

        // === COLLISION DETECTION ===
        if (serpent->autoCollision() && !serpent->firstMove()) {
            gameOver = true;
        }

        // === FRUIT HANDLING ===
        if(frutto->check(serpent)){
            // Snake ate the fruit - clear it and add points
            mvwaddch(win, frutto->yPos(), frutto->xPos(), ' ');
            lastAppleCheck = clock();
            frutto->off();
            scoreSnake += bonusPoints;
            punteggioFinale = scoreSnake;  // Update global score for saving
        }

        // Spawn new fruit if needed
        if (!frutto->isOn() && now - lastAppleCheck >= appleDelay) {
            spawnFruit(win, frutto, fruitX, fruitY);
        }

        // === LEVEL COMPLETION CHECK ===
        if(tempoPassato >= levelDelay){
            Utils::wait(500);
            
            // Show level completion screen
            werase(win);
            box(win, 0, 0);
            mvwprintw(win, Maxy/2 - 1, Maxx/2 - 10, "Level Completed!");
            mvwprintw(win, Maxy/2, Maxx/2 - 10, "Bonus: %d", bonusPoints);
            mvwprintw(win, Maxy/2 + 1, Maxx/2 - 10, "Press ESC to continue");
            scoreSnake += bonusPoints;
            punteggioFinale = scoreSnake;  // Update global score for saving
            displayScore(wrap);
            wrefresh(win);
            
            // Wait for ESC or ENTER to continue
            while(1){
                int c = wgetch(win);
                if (c == ESC_KEY || c == ENTER_KEY) {
                    delwin(win);
                    delwin(wrap);
                    break;
                }  
            }
            return BYPASSGAMEOVER;
        }

        // === RENDERING ===
        serpent->display();  // Draw snake
        box(win, 0, 0);      // Draw game border
        wrefresh(win);       // Refresh display

        // === GAME END CONDITIONS ===
        if (gameOver) {
            // Cleanup game objects
            delete serpent;
            delete frutto;
            delete livello;

            // Cleanup windows
            delwin(win);
            delwin(wrap);
            return GAME_OVER_COLLISION;  // Game ended by collision
        }
    }

    // This should never be reached due to infinite loop above
    delwin(win);
    delwin(wrap);
    return (tempoPassato > 0) ? scoreSnake : 0;
}

// ========== PAUSE MENU FUNCTION ==========

// Display pause menu and handle user choice
// Returns: true = resume game, false = exit to main menu
bool showPauseMenu(WINDOW* gameWin) {
    // Clear any buffered input before showing menu
    flushinp();
    
    // === CREATE PAUSE MENU WINDOW ===
    int menuHeight = 8;
    int menuWidth = 20;
    int yMax, xMax;
    getmaxyx(stdscr, yMax, xMax);
    int startY = (yMax - menuHeight) / 2;
    int startX = (xMax - menuWidth) / 2;
    
    WINDOW* pauseWin = newwin(menuHeight, menuWidth, startY, startX);
    keypad(pauseWin, TRUE);        // Enable arrow keys
    nodelay(pauseWin, FALSE);      // Make input blocking for menu navigation
    
    // === MENU OPTIONS ===
    const char* options[] = {"Ritorna al gioco", "Torna al menu"};
    int numOptions = 2;
    int highlight = 1;  // Currently highlighted option (1-based)
    int choice = 0;     // User's final choice (0 = none selected yet)
    
    // === MENU LOOP ===
    while (true) {
        // Draw pause menu background and title
        werase(pauseWin);
        box(pauseWin, 0, 0);
        mvwprintw(pauseWin, 1, (menuWidth - 13) / 2, "GIOCO IN PAUSA");
        
        // Draw menu options (highlight the selected one)
        for (int i = 0; i < numOptions; i++) {
            int y = 3 + i;
            int x = (menuWidth - strlen(options[i])) / 2;
            
            if (highlight == i + 1) {
                // Highlight selected option
                wattron(pauseWin, A_REVERSE);
                mvwprintw(pauseWin, y, x, "%s", options[i]);
                wattroff(pauseWin, A_REVERSE);
            } else {
                // Normal option display
                mvwprintw(pauseWin, y, x, "%s", options[i]);
            }
        }
        wrefresh(pauseWin);
        
        // === INPUT HANDLING ===
        flushinp();  // Clear buffered input
        int c = wgetch(pauseWin);
        
        switch (c) {
            case KEY_UP:
                // Move highlight up (wrap to bottom if at top)
                highlight = (highlight == 1) ? numOptions : highlight - 1;
                break;
            case KEY_DOWN:
                // Move highlight down (wrap to top if at bottom)
                highlight = (highlight == numOptions) ? 1 : highlight + 1;
                break;
            case ENTER_KEY: // Enter key
                choice = highlight;
                break;
            case ESC_KEY: // ESC key - resume game
                choice = 1;
                break;
        }
        
        // Exit loop when user makes a choice
        if (choice != 0) break;
    }
    
    // === CLEANUP ===
    delwin(pauseWin);
    flushinp();           // Clear input buffer before returning to game
    wrefresh(gameWin);    // Redraw the game window
    
    return (choice == 1); // true = resume game, false = exit to menu
}



