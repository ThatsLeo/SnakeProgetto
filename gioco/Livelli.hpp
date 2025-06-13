#ifndef LIVELLI_HPP
#define LIVELLI_HPP

#include "../includes/include.h"

/**
 * @brief Level class - manages game levels and level selection
 * 
 * This class implements a doubly linked list structure for managing
 * game levels, allowing navigation between levels and providing
 * level-specific configurations.
 */
class level {
public:
    // ========== CONSTRUCTORS ==========
    /**
     * @brief Default constructor
     */
    level();

    /**
     * @brief Parameterized constructor
     * @param id Level identifier
     * @param next Pointer to next level
     * @param prev Pointer to previous level
     */
    level(int id, level* next, level* prev) {
        this->id = id;
        this->next = next;
        this->prev = prev;
    }

    // ========== NAVIGATION METHODS ==========
    /**
     * @brief Navigate to next level
     */
    void nextLevel();

    /**
     * @brief Navigate to previous level
     */
    void prevLevel();

    /**
     * @brief Set current level by ID
     * @param id Level identifier to set
     */
    void setLevel(int id);

    // ========== DISPLAY METHODS ==========
    /**
     * @brief Print available levels in menu window
     * @param win Menu window pointer
     */
    void PrintLevels(WINDOW* win);

    // ========== INPUT HANDLING ==========
    /**
     * @brief Process user input for level selection
     * @param c Input character/key code
     * @return Processing result code
     */
    int processInput(int c);

    // ========== GETTERS ==========
    /**
     * @brief Get current level ID
     * @return Current level identifier
     */
    int getId();

    // ========== PUBLIC MEMBERS ==========
    int n_levels;       // Total number of levels

private:
    // ========== PRIVATE MEMBERS ==========
    int id;             // Level identifier
    level* next;        // Pointer to next level
    level* prev;        // Pointer to previous level
    level* currentlvl;  // Pointer to current level
    level* head;        // Pointer to first level
    level* tail;        // Pointer to last level
};

#endif // LIVELLI_HPP