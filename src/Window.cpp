#include "Window.h"
#include <SDL2/SDL_image.h>
#include <iostream>

Window::Window(std::string title, int width, int height)
{
    window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, 0);
    if (window != NULL)
    {
        printf("%s\n", SDL_GetError());
    }
    renderer = SDL_CreateRenderer(window, -1, 0);
    if (renderer == NULL)
    {
        printf("%s\n", SDL_GetError());
    }
    this->width = width;
    this->height = height;
}

Window::Window()
{

}

void Window::Show()
{
    SDL_ShowWindow(window);
}

void Window::Close()
{
    if (renderer != NULL)
    {
        SDL_DestroyRenderer(renderer);
        renderer = NULL;
    }
    if (window != NULL)
    {
        SDL_DestroyWindow(window);
        window = NULL;
    }
}

void Window::Draw(Texture texture, SDL_Rect src, SDL_Rect dst)
{
    SDL_Rect* src_ptr = &src;
    SDL_Rect* dst_ptr = &dst;
    if (SDL_RectEmpty(&dst) == SDL_TRUE)
    {
        dst_ptr = NULL;
        std::cout << "dst is empty" << std::endl; 
    }
    /*else
    {
        std::cout << "dst: " << "x: " << dst.x << " width: " << dst.w << " y: " << dst.y << " height: " << dst.h << std::endl;
    }*/
    if (SDL_RectEmpty(src_ptr) == SDL_TRUE)
    {
        src_ptr = NULL;
        std::cout << "src is empty" << std::endl; 
    }
    /*else 
    {
        //std::cout << "dst: " << "x: " << src.x << " width: " << src.w << " y: " << src.y << " height: " << src.h << std::endl;
    }*/
    texture.Draw(renderer, src_ptr, dst_ptr);
}

void Window::Draw(Platform platform)
{
    platform.Draw(renderer);
}

void Window::DrawRect(SDL_Rect* dst)
{
    if (dst == NULL)
    {
        SDL_RenderClear(renderer);
    }
    else 
    {
        SDL_RenderDrawRect(renderer, dst);
    }
}

void Window::DrawPixel(int x, int y)
{
    SDL_RenderDrawPoint(renderer, x,y);
}

void Window::DrawLevel(Level level)
{
    const std::list<Platform> layout = level.GetLevelLayout();
    for (auto it = layout.begin(); it != layout.end(); it++)
    {
        it->Draw(this->renderer);
    }
}

void Window::SetColor(SDL_Color color)
{
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void Window::SetColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
    SDL_SetRenderDrawColor(renderer, r, g, b, a);
}

Texture Window::MakeTexture(std::string path)
{
    SDL_Surface* tempSurface = IMG_Load(path.c_str());
    if (tempSurface == NULL)
    {
        printf("%s\n", IMG_GetError());
        return NULL;
    }
    else
    {
        SDL_Texture* tempTexture = SDL_CreateTextureFromSurface(renderer, tempSurface);
        if (tempTexture == NULL)
        {
            printf("%s\n", SDL_GetError());
            return NULL;
        }
        else 
        {
            return Texture(tempTexture);
        }
    }
}

int Window::GetWidth()
{
    return width;
}

int Window::GetHeight()
{
    return height;
}

void Window::FrameReady()
{
    SDL_RenderPresent(renderer);
}