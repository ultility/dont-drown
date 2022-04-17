#include "Level.h"
#include "Player.h"

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

std::list<Platform> Level::GetColliding(Player p)
{
    std::list<Platform> colliding;
    for (auto it = blocks.begin(); it != blocks.end(); it++)
    {
        if (p.IsColliding(*it))
        {
            colliding.push_back(*it);
        }
    }
    return colliding;
}