#ifndef SERPENTE_HPP
#define SERPENTE_HPP

#include "../includes/include.h"
#include "../utils/utils.h"

/**
 * @file Serpente.hpp
 * @brief Snake entity class and related structures for the Snake game
 * 
 * This file contains the main snake entity implementation including
 * movement logic, collision detection, and rendering functionality.
 */

// ========== ENUMERATIONS ==========

/**
 * @brief Direction enumeration for snake movement
 * 
 * Defines the four possible movement directions for the snake.
 */
enum Direction {
    UP,    ///< Move upward
    DOWN,  ///< Move downward  
    LEFT,  ///< Move leftward
    RIGHT  ///< Move rightward
};

// ========== STRUCTURES ==========

/**
 * @brief Body segment structure for the snake
 * 
 * Represents a single segment of the snake's body using a linked list
 * structure to efficiently manage dynamic length changes.
 */
struct body {
    int y;           ///< Y coordinate of the body segment
    int x;           ///< X coordinate of the body segment
    body* next;      ///< Pointer to the next body segment
};

// ========== CLASSES ==========

/**
 * @brief Main Snake class
 * 
 * Handles all snake-related functionality including movement, growth,
 * collision detection, and rendering. The snake is implemented as a
 * linked list of body segments for efficient dynamic resizing.
 */
class Serpente {
public:
    // ========== PUBLIC MEMBERS ==========
    Direction dir;   ///< Current movement direction
    
    // ========== CONSTRUCTORS ==========
    
    /**
     * @brief Construct a new Snake object
     * 
     * @param win Pointer to the ncurses window for rendering
     * @param c Character used to represent the snake on screen
     * @param length Initial length of the snake
     */
    Serpente(WINDOW* win, char c, int length);
    
    // ========== POSITION & STRUCTURE METHODS ==========
    
    /**
     * @brief Get the head position of the snake
     * @return body* Pointer to the head segment
     */
    body* getHeadPos();
    
    /**
     * @brief Get the tail position of the snake
     * @return body* Pointer to the tail segment
     */
    body* tail();
    
    /**
     * @brief Get the segment before the tail
     * @return body* Pointer to the second-to-last segment
     */
    body* prevTail();
    
    /**
     * @brief Add a new body segment at specified coordinates
     * 
     * @param y Y coordinate for the new segment
     * @param x X coordinate for the new segment
     * @return body* Pointer to the newly created segment
     */
    body* addBody(int y, int x);
    
    // ========== MOVEMENT METHODS ==========
    
    /**
     * @brief Perform default movement based on current direction
     */
    void defaultMove();
    
    /**
     * @brief Move the snake upward
     */
    void moveUp();
    
    /**
     * @brief Move the snake downward
     */
    void moveDown();
    
    /**
     * @brief Move the snake leftward
     */
    void moveLeft();
    
    /**
     * @brief Move the snake rightward
     */
    void moveRight();
    
    /**
     * @brief Execute movement based on current direction
     */
    void move();
    
    // ========== INPUT HANDLING ==========
    
    /**
     * @brief Get the current movement input
     * @return int Key code representing the desired movement
     */
    int getMove();
    
    /**
     * @brief Set movement direction based on key input
     * 
     * @param key Key code from user input
     */
    void setMove(int key);
    
    // ========== COLLISION & GAME LOGIC ==========
    
    /**
     * @brief Check if this is the snake's first movement
     * @return true If this is the first move
     * @return false If the snake has already moved
     */
    bool firstMove();
    
    /**
     * @brief Check for collision with the snake's own body
     * @return true If collision detected
     * @return false If no collision
     */
    bool autoCollision();
    
    // ========== RENDERING METHODS ==========
    
    /**
     * @brief Display the snake on the screen
     */
    void display();
    
    /**
     * @brief Clear the snake from the screen
     */
    void blank();
    
    // ========== TIMING METHODS ==========
    
    /**
     * @brief Get the current sleep time for movement delays
     * @return int Sleep time in milliseconds
     */
    int getSleepTime() {
        return SleepTime;
    }
    
    /**
     * @brief Set the sleep time for movement delays
     * @param time Sleep time in milliseconds
     */
    void setSleepTime(int time) {
        SleepTime = time;
    }

private:
    // ========== PRIVATE MEMBERS ==========
    
    int headX, headY;    ///< Head position coordinates
    body* head;          ///< Pointer to the head segment
    char character;      ///< Character used for rendering
    WINDOW* win;         ///< Pointer to the ncurses window
    int SleepTime = 0;   ///< Movement delay in milliseconds
    
    // ========== PRIVATE METHODS ==========
    
    /**
     * @brief Move the snake by specified offset
     * 
     * @param dx X offset for movement
     * @param dy Y offset for movement
     */
    void moveBy(int dx, int dy);
};

#endif // SERPENTE_HPP


