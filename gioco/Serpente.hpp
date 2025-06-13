#ifndef SERPENTE_HPP
#define SERPENTE_HPP

#include "../includes/include.h"
#include "../utils/utils.h"

// ========== ENUMERATIONS ==========
/**
 * @brief Direction enumeration for snake movement
 */
enum Direction { 
    UP, 
    DOWN, 
    LEFT, 
    RIGHT 
};

// ========== STRUCTURES ==========
/**
 * @brief Snake body segment structure (linked list node)
 */
struct body {
    int y;              // Y coordinate
    int x;              // X coordinate
    body* next;         // Pointer to next segment
};

/**
 * @brief Snake class - manages snake movement, collision, and display
 * 
 * This class implements the snake as a linked list of body segments,
 * handling movement, growth, collision detection, and rendering.
 */
class Serpente {
public:
    // ========== PUBLIC MEMBERS ==========
    Direction dir;      // Current movement direction

    // ========== CONSTRUCTORS ==========
    /**
     * @brief Construct a new Serpente object
     * @param win Game window pointer
     * @param c Character to display for snake segments
     * @param length Initial length of the snake
     */
    Serpente(WINDOW* win, char c, int length);

    // ========== MOVEMENT METHODS ==========
    /**
     * @brief Get pointer to snake head position
     * @return Pointer to head body segment
     */
    body* getHeadPos();

    /**
     * @brief Move snake in current direction
     */
    void defaultMove();

    /**
     * @brief Clear snake from display
     */
    void blank();

    /**
     * @brief Get pointer to previous tail segment
     * @return Pointer to tail segment
     */
    body* prevTail();

    /**
     * @brief Add new body segment at coordinates
     * @param y Y coordinate
     * @param x X coordinate
     * @return Pointer to new body segment
     */
    body* addBody(int y, int x);

    /**
     * @brief Get pointer to tail segment
     * @return Pointer to tail
     */
    body* tail();    // ========== DIRECTIONAL MOVEMENT ==========
    void moveUp();
    void moveDown();
    void moveLeft();
    void moveRight();

    // ========== INPUT HANDLING ==========
    /**
     * @brief Get current movement key
     * @return Current movement key code
     */
    int getMove();

    /**
     * @brief Set movement direction based on key input
     * @param key Key code for direction
     */
    void setMove(int key);

    /**
     * @brief Execute movement in current direction
     */
    void move();

    // ========== DISPLAY METHODS ==========
    /**
     * @brief Display snake on the game window
     */
    void display();

    // ========== TIMING METHODS ==========
    /**
     * @brief Get current sleep time between moves
     * @return Sleep time in milliseconds
     */
    int getSleepTime() {
        return SleepTime;
    }

    /**
     * @brief Set sleep time between moves
     * @param time Sleep time in milliseconds
     */
    void setSleepTime(int time) {
        SleepTime = time;
    }

    // ========== GAME STATE METHODS ==========
    /**
     * @brief Check if this is the snake's first move
     * @return true if first move, false otherwise
     */
    bool firstMove();

    /**
     * @brief Check for collision with snake's own body
     * @return true if collision detected, false otherwise
     */
    bool autoCollision();

private:
    // ========== PRIVATE MEMBERS ==========
    int headX, headY;       // Head coordinates
    body* head;             // Pointer to head segment
    char character;         // Display character
    WINDOW* win;            // Game window
    int SleepTime = 0;      // Movement delay

    // ========== PRIVATE METHODS ==========
    /**
     * @brief Move head by specified offset
     * @param dx X offset
     * @param dy Y offset
     */
    void moveBy(int dx, int dy);
};

#endif // SERPENTE_HPP