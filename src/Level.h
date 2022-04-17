#pragma once
#include "Platform.h"
#include "Texture.h"
#include <list>
class Player;
class Level
{
    public:
        void IncreaseTime(int timeToAdd);
        const std::list<Platform> GetLevelLayout();
        bool AddPlatform(Platform p);
        bool RemovePlatform(Platform p);
        std::list<Platform> GetColliding(Player p);
    private:
        std::list<Platform> blocks;
        int timeLeft;
};