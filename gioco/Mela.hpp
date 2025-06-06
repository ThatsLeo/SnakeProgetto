#include "../includes/include.h"
#pragma once

class Mela{
    public:
        Mela(WINDOW * win, int x, int y, char c);

        inline void wait(int milliseconds);

        void randPos(int x, int y);

        void Spawn(int x, int y);

        bool isOn();

        void off();

        bool check(Serpente *serp);

        int xPos();

        int yPos();

    private:
        WINDOW * win;
        int x;
        int y;
        char character;
};

