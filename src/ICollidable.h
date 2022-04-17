#pragma once
#include <SDL2/SDL.h>

class ICollidable
{
    public:
        inline virtual bool IsColliding(SDL_Rect other){return false;}
};