#include "player.h"
#include "SDL2/SDL_timer.h"
#include <iostream>

bool Player::movementLock;
const int STEP_SIZE = 5;
const int STEP_LOCK_TIME = 50;

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
    window.Draw(texture, src, dst);
}

void Player::HandleInput(SDL_Event e)
{
    if (Player::movementLock)
    {
        return;
    }
    switch (e.key.keysym.sym)
    {
        case SDLK_RIGHT:
        case SDLK_d:
            x += STEP_SIZE;
            Player::movementLock = true;
            SDL_AddTimer(STEP_LOCK_TIME,UnlockMovement, 0);
            std::cout << x << std::endl;
            break;
        case SDLK_LEFT:
        case SDLK_a:
            x -= STEP_SIZE;
            Player::movementLock = true;
            SDL_AddTimer(STEP_LOCK_TIME,UnlockMovement, 0);
            std::cout << x << " " << y << std::endl;
            break;
    }
}

