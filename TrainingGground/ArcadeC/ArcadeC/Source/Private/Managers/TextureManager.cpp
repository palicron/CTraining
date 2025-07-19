
#include "../../Public/Managers/TextureManager.h"
#include "SDL3_image/SDL_image.h"
#include "../../Public/Game.h"
#include <filesystem>
#include <__msvc_filebuf.hpp>

SDL_Texture* TextureManager::LoadTexture(const char* fileName, SDL_Renderer* renderer)
{
    SDL_Surface* tmp_Surface = IMG_Load(fileName);

    if (!tmp_Surface)
    {
        return nullptr;
    }

    SDL_Texture* tmp_Texture = SDL_CreateTextureFromSurface(renderer, tmp_Surface);
    SDL_DestroySurface(tmp_Surface);
    return tmp_Texture;
}

void TextureManager::Draw(SDL_Texture* texture,SDL_FRect* sourceRect, SDL_FRect* destinationRect)
{
    if (!texture)
    {
        return;
    }
    
    SDL_RenderTexture(Game::GetRenderer(),texture,sourceRect,destinationRect);
}
