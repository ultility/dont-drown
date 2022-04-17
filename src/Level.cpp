#include "Level.h"

const std::list<Platform> Level::GetLevelLayout()
{
    return blocks;
}

void Level::IncreaseTime(int timeToAdd)
{
    timeLeft += timeToAdd;
}

bool Level::AddPlatform(Platform p)
{
    std::list<Platform>::iterator it;
    for (it = blocks.begin(); it != blocks.end(); ++it)
    {
        if (*it==p)
        {
            return false;
        }
    }
    blocks.push_back(p);
    return true;
}

bool Level::RemovePlatform(Platform p)
{
    std::list<Platform>::iterator it;
    for (it = blocks.begin(); it != blocks.end(); ++it)
    {
        if (*it==p)
        {
            blocks.erase(it);
            return true;
        }
    }
    return false;
}