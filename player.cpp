#include "player.h"

#include <iostream>

using namespace std;

void player::move(){
    //Type 1 to move forward, type 0 to retreat"
    bool valid = false;
    int temp;
    while(!valid){
        cout << "Type 1 or 0" <<endl;
        std::cin >> temp;
        if(temp != 1 && temp != 0)
            cout << "Please enter a valid command!"<<endl;
        else{
            if(temp == 1){
                decision = true;
            }
            else{
                decision = false;

                score = score + bag;
                bag = 0;
                retreating = true;
            }
            valid = true;
        }
    }
    if(decision){
        std::cout << "You have decided to move forward!"<<std::endl;
        
    }
    else{
        std::cout << "You have decided to retreat!"<<std::endl;
    }
};

void player::addScore(int count){
    score = score + count;
}
