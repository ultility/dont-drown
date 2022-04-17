#pragma once
#include <SDL2/SDL.h>
class Texture
{
    public:
        SDL_Rect GetBounds();
        void Draw(SDL_Renderer* renderer, SDL_Rect* src, SDL_Rect* dst) const;
        void free();
        Texture(SDL_Texture* texture);
        Texture();
    private:
        SDL_Texture* texture;
        SDL_Rect bounds;
};