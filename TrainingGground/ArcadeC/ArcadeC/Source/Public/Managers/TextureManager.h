#pragma once
#include <SDL3/SDL_render.h>

class TextureManager
{
    
public:
    static SDL_Texture* LoadTexture(const char* fileName);
    static void Draw(SDL_Texture* texture,SDL_FRect* sourceRect, SDL_FRect* destinationRect);
};
