#pragma once
#include <SDL3/SDL_render.h>

class TextureManager
{
    
public:
    static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* renderer);
};
