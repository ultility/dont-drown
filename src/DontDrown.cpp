#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <iostream>
#include "Texture.h"
#include "Window.h"
#include "player.h"
#include "Level.h"

const int DEFAULT_WINDOW_WIDTH = 640;
const int DEFAULT_WINDOW_HEIGHT = 640;
const int WALL_THICCNESS = 5;

bool init(Window* w, int width = DEFAULT_WINDOW_WIDTH, int height = DEFAULT_WINDOW_HEIGHT, std::string title = "Dont Drown")
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0)
    {
        printf("%s\n", SDL_GetError());
        return false;
    }
    int imageInitOptions = IMG_INIT_PNG;
    if (IMG_Init(imageInitOptions) != imageInitOptions)
    {
        printf("%s\n", IMG_GetError());
        return false;
    }
    *w = Window(title, width, height);
    return true;
}

Level LoadLevel(Window w)
{   std::string path = "../images/stone";
    int random = rand()%(3-1+1) + 1;
    path += std::to_string(random);
    path += ".png";
    Platform leftWall(0,0,WALL_THICCNESS, w.GetHeight(), w.MakeTexture(path.c_str()));
    path = "../images/stone";
    random = rand()%(3-1+1) + 1;
    path += std::to_string(random);
    path += ".png";
    Platform rightWall(w.GetWidth() - WALL_THICCNESS, 0, WALL_THICCNESS, w.GetHeight(), w.MakeTexture(path.c_str()));
    Level level1;
    level1.AddPlatform(leftWall);
    level1.AddPlatform(rightWall);
    return level1;
}

int main()
{
    Window mainWindow;
    if (init(&mainWindow))
    {
        bool IsGameFinished = false;
        SDL_Event e;
        mainWindow.Show();
        Texture playerTexture = mainWindow.MakeTexture("../images/walking_stick_figure_1.png");
        Player player(mainWindow.GetWidth() / 2, mainWindow.GetHeight() / 2, 20, 50, mainWindow.MakeTexture("../images/walking_stick_figure_1.png"));
        Level currentLevel = LoadLevel(mainWindow);
        mainWindow.SetColor(255,255,255,255);
        while (!IsGameFinished)
        {
            while (SDL_PollEvent(&e))
            {
                switch (e.type)
                {
                    case SDL_EventType::SDL_QUIT:
                        IsGameFinished = true;
                        //SDL_SetRenderDrawColor(mainWindow.renderer, 255, 255,255,255);
                        break;
                    case SDL_EventType::SDL_KEYDOWN:
                        player.HandleInput(e);
                    default:
                        break;
                }
            }
            mainWindow.DrawRect();
            player.Draw(mainWindow);
            //mainWindow.DrawLevel(currentLevel);
            mainWindow.FrameReady();
        }
        
    }
}

