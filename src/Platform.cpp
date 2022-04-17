#include "Platform.h"
#include <iostream>

Platform::Platform(int x, int y, int width, int height, Texture texture)
{
    bounds.x = x;
    bounds.y = y;
    bounds.w = width;
    bounds.h = height;
    this->texture = texture;
}

bool Platform::IsColliding(SDL_Rect other) const
{
    int boundsRight = bounds.x + bounds.w;
    int boundsBottom = bounds.y + bounds.y;
    int otherRight = other.x + other.w;
    int otherBottom = other.y + other.h;
    return !(bounds.x > otherRight || 
            boundsRight < other.x || 
            bounds.y > otherBottom ||
            boundsBottom < other.y);
}

void Platform::Draw(SDL_Renderer* renderer) const
{
    
    SDL_Rect dst(bounds);    
    texture.Draw(renderer, NULL, &dst);
}

bool operator== (const Platform& p1, const Platform& p2)
{
    return p1.timeOfCreation == p2.timeOfCreation;
}