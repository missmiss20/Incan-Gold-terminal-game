#ifndef ADVENTURE_H
#define ADVENTURE_H

#include "player.h"

#include <string>
#include <vector>
#include <iostream>
#include <utility>

class adventure{
    public:
        adventure(int playerNumber);
        ~adventure();
        void game();
        void summary();
        
        

    private:
        size_t playerNumber = 0; //玩家数量
        size_t rounds = 3;  //游戏一共三个回合
        int leftover = 0;  //剩余财宝
        std::vector<std::pair<std::string, int>> cards; //存放卡牌
        std::vector<player*> players; //存放玩家
        
        int cardCount = 0;  //剩余卡片数量

        void round();
        void turn();
        int getWordCount(std::string word) const;
        int generate();
};

#endif
