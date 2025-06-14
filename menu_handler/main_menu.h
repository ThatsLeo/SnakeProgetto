#ifndef MAIN_MENU_H
#define MAIN_MENU_H

#include "../includes/include.h"
#include "../utils/utils.cpp"
#include "../file_handler/file_manager.cpp"

/**
 * @brief Menu class - handles main menu functionality
 * 
 * This class manages the main menu interface, including navigation,
 * game launching, leaderboard display, and level selection.
 */
class Menu {
public:
    // ========== CONSTRUCTORS & DESTRUCTORS ==========
    /**
     * @brief Construct a new Menu object
     */
    Menu();

    /**
     * @brief Destroy the Menu object
     */
    ~Menu();

    // ========== PUBLIC INTERFACE ==========
    /**
     * @brief Close the menu (cleanup)
     */
    void close_menu();

    /**
     * @brief Start the main menu loop
     */
    void start_menu();

private:
    // ========== PRIVATE METHODS ==========
    
    /**
     * @brief Print menu options to screen
     */
    void print_menu();    /**
     * @brief Display the SNAKE title in its own window
     */
    void displayTitle();

    /**
     * @brief Remove the title window from screen
     */
    void removeTitle();

    /**
     * @brief Process user input for menu navigation
     * @param c Input character/key code
     */
    void process_input(int c);

    /**
     * @brief Handle user input and return selection
     * @return Selected menu option
     */
    int handle_user_input();

    /**
     * @brief Handle game over scenarios
     * @param game_state Game ending state code
     */
    void gameOver(int game_state);

    // ========== PRIVATE MEMBERS ==========
    WINDOW* menu_win;           // Menu window pointer
    int highlight;              // Currently highlighted option
    int choice;                 // Current user choice
    int old_choice;             // Previous choice for refresh
    int n_choices;              // Total number of menu options
    const char* choices[4];     // Menu option strings

    int starty;                 // Window start Y coordinate
    int startx;                 // Window start X coordinate
};

#endif // MAIN_MENU_H
    