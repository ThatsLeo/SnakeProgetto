// ----------------- IMPORTANTE ---------------------------------------------
// usate sto file per aggiungere tutte le librerie che vi servono in tutti i file
// in modo da non doverle aggiungere ogni volta

// Also make global variables here and global functions
// --------------------------------------------------------------
#pragma once

// ----------------- IMPORTANTE ---------------------------------------------
// usate sto file per aggiungere tutte le librerie che vi servono in tutti i file
// in modo da non doverle aggiungere ogni volta

// Also make global variables here and global functions
// --------------------------------------------------------------
#pragma once

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
