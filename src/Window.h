#pragma once
#include <SDL2/SDL.h>
#include <string>
#include "Texture.h"
#include "Level.h"

class Window
{
    public:
        void Draw(Texture texture, SDL_Rect src, SDL_Rect dst);
        void Draw(Platform platform);
        Texture MakeTexture(std::string);
        void Close();
        void Show();
        void SetColor(SDL_Color c);
        void SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);
        void DrawRect(SDL_Rect* dst = NULL);
        void DrawPixel(int x, int y);
        void DrawLevel(Level level);
        void FrameReady();
        int GetWidth();
        int GetHeight();
        Window(std::string title, int width, int height);
        Window();
    private:
        SDL_Renderer* renderer;
        SDL_Window* window;
        int width;
        int height;
};