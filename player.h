#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <iostream>

class player{
    public:
        void move();
        void addScore(int count);

        size_t score = 0; //kept score
        size_t bag = 0;  //temp score
        bool decision = true;
        bool retreating = false;

};

#endif