#include "Texture.h"
#include <stdio.h>
Texture::Texture(SDL_Texture* texture)
{
    this->texture = texture;
    SDL_QueryTexture(texture, NULL, NULL, &bounds.w, &bounds.h);
}

Texture::Texture()
{
    
}

void Texture::Draw(SDL_Renderer* renderer, SDL_Rect* src, SDL_Rect* dst) const
{
    if (SDL_RenderCopy(renderer, texture, src, dst) != 0)
    {
        printf("%s\n", SDL_GetError());
    }
}

SDL_Rect Texture::GetBounds()
{
    return bounds;
}

void Texture::free()
{
    if (texture != NULL)
    {
        SDL_DestroyTexture(texture);
        texture == NULL;
    }
}