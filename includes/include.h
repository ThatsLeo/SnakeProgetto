#ifndef INCLUDE_H
#define INCLUDE_H
#pragma once

#include <ncurses/ncurses.h>
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>

#define Maxy 20                 // altezza griglia
#define Maxx 50                 // larghezza griglia
#define BYPASSGAMEOVER 12938    // valore per bypass della scritta gameOver
#define ESC_KEY 27              // int esc
#define ENTER_KEY 10            // int enter
#define GAME_OVER_COLLISION 0   // valore per collisione

static int levelChosen = 1;    
extern int punteggioFinale; 

#endif
