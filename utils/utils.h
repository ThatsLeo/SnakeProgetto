#ifndef UTILS_H
#define UTILS_H

#include "../includes/include.h"

// ========== CONSTANTS ==========
#define BYPASSGAMEOVER 12938    // Return code for bypassing game over

// ========== GLOBAL VARIABLES ==========
extern int punteggioFinale;     // Final score for saving

/**
 * @brief Utility class - provides static helper functions
 * 
 * This class contains static utility functions for window creation,
 * color initialization, timing, and other common operations.
 */
class Utils {
public:
    // ========== WINDOW CREATION ==========
    /**
     * @brief Create a centered box window
     * @param boxForFile Window pointer (will be overwritten)
     * @param heightDivisor Height divisor for sizing
     * @param widthDivisor Width divisor for sizing
     * @return Pointer to created window
     */
    static WINDOW* CreateBoxWindowCentered(WINDOW* boxForFile, int heightDivisor, int widthDivisor);

    /**
     * @brief Create a text input box
     * @param boxForFile Window pointer (will be overwritten)
     * @param characters Number of characters width
     * @param starty Starting Y coordinate
     * @param startx Starting X coordinate
     * @return Pointer to created window
     */
    static WINDOW* CreateTextBox(WINDOW* boxForFile, int characters, int starty, int startx);

    // ========== TEXT DISPLAY ==========
    /**
     * @brief Display inlined text in window
     * @param insideBox Target window
     * @param x X coordinate
     * @param y Y coordinate
     * @param buffer Text buffer to display
     */
    static void InlinedTextWindow(WINDOW* insideBox, int x, int y, char* buffer);

    // ========== COLOR MANAGEMENT ==========
    /**
     * @brief Initialize color pairs for ncurses
     */
    static void initColors();

    // ========== TIMING ==========
    /**
     * @brief Wait for specified milliseconds
     * @param milliseconds Time to wait in milliseconds
     */
    static void wait(int milliseconds);
};

#endif // UTILS_H