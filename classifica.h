#ifndef CLASSIFICA_H
#define CLASSIFICA_H

#include "includes/include.h"

/**
 * @brief Classifica class - handles leaderboard functionality
 * 
 * This class provides static methods for displaying and managing
 * the game's leaderboard/ranking system.
 */
class Classifica {
public:
    // ========== LEADERBOARD OPERATIONS ==========
    /**
     * @brief Start and display the leaderboard interface
     * 
     * Shows the current leaderboard with top scores, including
     * colored highlighting for top 3 positions and player names.
     */
    static void start_classifica();
};

#endif // CLASSIFICA_H