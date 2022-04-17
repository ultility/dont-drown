#pragma once
#include <SDL2/SDL.h>
#include "Texture.h"
#include "ICollidable.h"

class Platform : ICollidable
{
    public:
        void Draw(SDL_Renderer* renderer) const;
        bool IsColliding(SDL_Rect other) const;
        Platform(int x, int y, int width, int height, Texture texture = NULL);
        void SetTexture(Texture texture);
        friend bool operator==(const Platform& p1, const Platform& p2);
    private:
        SDL_Rect bounds;
        Texture texture;
        int timeOfCreation;
};