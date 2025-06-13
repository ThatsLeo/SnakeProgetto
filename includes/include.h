#ifndef INCLUDE_H
#define INCLUDE_H

/**
 * @brief Global includes and definitions
 * 
 * This file contains all common library includes, global constants,
 * and shared definitions used throughout the Snake game project.
 */

// ========== LIBRARY INCLUDES ==========
#include <ncurses/ncurses.h>
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>

// ========== GAME CONSTANTS ==========
#define Maxy 20                 // Game area height
#define Maxx 50                 // Game area width

// ========== GLOBAL VARIABLES ==========
static int levelChosen = 1;    // Currently selected level (default: 1)

#endif // INCLUDE_H
