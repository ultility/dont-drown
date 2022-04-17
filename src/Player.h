#pragma once
#include <SDL2/SDL.h>
#include "Texture.h"
#include "Platform.h"
#include "Level.h"
class Window;
class Player
{
    public:
        Player(int x, int y, int width, int height, Texture texture = NULL);
        void HandleInput(SDL_Event e);
        void Update(Level currentLevel);
        void Draw(Window window);
        bool IsColliding(Platform p);
        static bool movementLock;
    private:
        int dy = 0;
        int dx = 0;
        int x;
        int y;
        int height;
        int width;
        Texture texture;
        bool isStanding;
};