#include "Player.h"
#include "SDL2/SDL_timer.h"
#include <iostream>
#include "Window.h"

bool Player::movementLock;
const int STEP_SIZE = 5;
const int STEP_LOCK_TIME = 50;
const int JUMP_HEIGHT = 50;
const int JUMP_TIME = 15;

Uint32 UnlockMovement( Uint32 interval, void* param )
{
    Player::movementLock = false;
	return 0;
}

Player::Player(int x, int y, int width, int height, Texture texture)
{
    this->texture = texture;
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

void Player::Draw(Window window)
{
    SDL_Rect dst;
    SDL_Rect src;
    dst.x = this->x;
    dst.y = this->y;
    dst.w = this->width;
    dst.h = this->height;
    src.h = 0;
    src.w = 0;
    src.x = 0;
    src.y = 0;
    window.Draw(texture, src, dst);
}

void Player::HandleInput(SDL_Event e)
{
    switch (e.key.keysym.sym)
    {
        case SDLK_RIGHT:
        case SDLK_d:
            dx = (e.type == SDL_EventType::SDL_KEYDOWN)? STEP_SIZE : 0;
            std::cout << x << " " << y << std::endl;
            break;
        case SDLK_LEFT:
        case SDLK_a:
            dx = (e.type == SDL_EventType::SDL_KEYDOWN)? -STEP_SIZE : 0;
            std::cout << x << " " << y << std::endl;
            break;
        case SDLK_UP:
        case SDLK_w:
            if (isStanding && e.type == SDL_EventType::SDL_KEYDOWN)
            {
                dy = -JUMP_HEIGHT / JUMP_TIME;
            }
            break;
    }

}

void Player::Update(Level currentLevel)
{
    std::list<Platform> colliding = currentLevel.GetColliding(*this);
    bool isFloating = !isStanding;
    y += dy;
    for (auto it = colliding.begin(); it != colliding.end(); it++)
    {
        const SDL_Rect current = (*it).GetBounds();
        
        if(current.y < y + height) // player bottom colliding with platform top
        {
            y = current.y - height; // touching
            dy = 0;
            isFloating = false;
        }
        else if(current.y + current.h < y) // player top colliding with platform bottom
        {
            dy = 0;
            y = current.y + current.h; // touching
        }
        if(current.y == y + height) // player bottom touching with platform top
        {
            dy = 0;
            isFloating = false;

        }
        else
        {
            isFloating = true;
        }
    }
    if (isFloating && dy == 0)
    {
        dy = JUMP_HEIGHT / JUMP_TIME;
    }
    isStanding = !isFloating;
    if (movementLock)
    {
        return;
    }
    colliding = currentLevel.GetColliding(*this);
    Player::movementLock = true;
    SDL_AddTimer(STEP_LOCK_TIME,UnlockMovement, NULL);
    x += dx;
    int i = 1;
    for (auto it = colliding.begin(); it != colliding.end(); ++it, i++)
    {
        std::cout << "platform #" << i << std::endl;
        const SDL_Rect current = (*it).GetBounds();
        if(current.y == y + height) // player bottom touching with platform top
        {
            std::cout << current.y << "\t" << y + height << std::endl;
            continue;
        }
        if (current.x < x + width) // player right colliding with platform left
        {
            //std::cout << current.y << "\t" << y + height << std::endl; 
            x = current.x - width - 1; // not touching
        }
        else if (current.x + current.w > x) // player left colliding with platform right
        {
            //std::cout << current.y << "\t" << y + height << std::endl;
            x = current.x + current.w + 1; // not touching
        }
    }
}

bool Player::IsColliding(Platform p)
{
    SDL_Rect bounds;
    bounds.h = height;
    bounds.w = width;
    bounds.x = x;
    bounds.y = y;
    return p.IsColliding(bounds);
}