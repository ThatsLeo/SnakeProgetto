#ifndef MELA_HPP
#define MELA_HPP

#include "../includes/include.h"

// Forward declaration
class Serpente;

/**
 * @brief Apple class - manages fruit spawning, position, and collision detection
 * 
 * This class handles the apple/fruit object in the Snake game, including
 * random positioning, display, and collision detection with the snake.
 */
class Mela {
public:
    // ========== CONSTRUCTORS ==========
    /**
     * @brief Construct a new Mela object
     * @param win Game window pointer
     * @param x Initial X coordinate
     * @param y Initial Y coordinate  
     * @param c Character to display for the apple
     */
    Mela(WINDOW* win, int x, int y, char c);

    // ========== PUBLIC METHODS ==========
    /**
     * @brief Generate random position for the apple
     * @param x Maximum X coordinate
     * @param y Maximum Y coordinate
     */
    void randPos(int x, int y);

    /**
     * @brief Spawn apple at specific coordinates
     * @param x X coordinate
     * @param y Y coordinate
     */
    void Spawn(int x, int y);

    /**
     * @brief Check if apple is currently active/visible
     * @return true if apple is on screen, false otherwise
     */
    bool isOn();

    /**
     * @brief Turn off/hide the apple
     */
    void off();

    /**
     * @brief Check if snake collided with the apple
     * @param serp Pointer to the snake object
     * @return true if collision detected, false otherwise
     */
    bool check(Serpente* serp);

    /**
     * @brief Get apple's X coordinate
     * @return Current X position
     */
    int xPos();

    /**
     * @brief Get apple's Y coordinate  
     * @return Current Y position
     */
    int yPos();

private:
    // ========== PRIVATE MEMBERS ==========
    WINDOW* win;        // Game window
    int x;              // X coordinate
    int y;              // Y coordinate
    char character;     // Display character
    bool active;        // Active state flag
};

#endif // MELA_HPP
