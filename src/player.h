#pragma once
#include <SDL2/SDL.h>
#include "Texture.h"
#include "Window.h"
class Player
{
    public:
        Player(int x, int y, int width, int height, Texture texture = NULL);
        void HandleInput(SDL_Event e);
        void Draw(Window window);

        static bool movementLock;
    private:
        int x;
        int y;
        int height;
        int width;
        Texture texture;
};