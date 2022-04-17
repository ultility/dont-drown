#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include <iostream>
#include "Texture.h"
#include "Window.h"
#include "Player.h"
#include "Level.h"

const int DEFAULT_WINDOW_WIDTH = 640;
const int DEFAULT_WINDOW_HEIGHT = 640;
const int WALL_THICCNESS = 5;
const int MAX_FPS = 60;

Uint32 nextFrameCountdown(Uint32 interval, void* param)
{
    *(bool*)param = false;
    return 0;
}

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

std::string randomTexturePath(std::string base, int amount, std::string ending)
{
    base += std::to_string((rand()%amount) + 1);
    base += ending;
    return base;
}

Level LoadLevel(Window w)
{   
    std::string path = randomTexturePath("../images/stone", 3, ".png");
    Platform leftWall(0,0,WALL_THICCNESS, w.GetHeight(), w.MakeTexture(path.c_str()));
    path = randomTexturePath("../images/stone", 3, ".png");
    Platform rightWall(w.GetWidth() - WALL_THICCNESS, 0, WALL_THICCNESS, w.GetHeight(), w.MakeTexture(path.c_str()));
    path = randomTexturePath("../images/stone", 3, ".png");
    Platform floor(0,w.GetHeight() - WALL_THICCNESS, w.GetWidth(), WALL_THICCNESS, w.MakeTexture(path));
    Level level1;
    level1.AddPlatform(leftWall);
    level1.AddPlatform(rightWall);
    level1.AddPlatform(floor);
    return level1;
}

int main()
{
    Window mainWindow;
    if (init(&mainWindow))
    {
        bool IsGameFinished = false;
        bool frameLock = false;
        SDL_Event e;
        mainWindow.Show();
        Texture playerTexture = mainWindow.MakeTexture("../images/walking_stick_figure_1.png");
        Player player(mainWindow.GetWidth() / 2, mainWindow.GetHeight() / 2, 20, 50, mainWindow.MakeTexture("../images/walking_stick_figure_1.png"));
        Level currentLevel = LoadLevel(mainWindow);
        mainWindow.SetColor(255,255,255,255);
        SDL_TimerID timerId;
        while (!IsGameFinished)
        {
            if (!frameLock)
            {
                timerId = SDL_AddTimer(1000/MAX_FPS, nextFrameCountdown, (void*)&frameLock);
                frameLock = true;
                while (SDL_PollEvent(&e))
                {
                    switch (e.type)
                    {
                        case SDL_EventType::SDL_QUIT:
                            IsGameFinished = true;
                            break;
                        case SDL_EventType::SDL_KEYDOWN:
                        case SDL_EventType::SDL_KEYUP:
                            player.HandleInput(e);
                        default:
                            break;
                    }
                }
                player.Update(currentLevel);
                mainWindow.DrawRect();
                player.Draw(mainWindow);
                mainWindow.DrawLevel(currentLevel);
                mainWindow.FrameReady();
            }
        }
        
    }
}

