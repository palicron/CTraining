#pragma once
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>

class TileMap
{
public:

    TileMap();
    ~TileMap();

    void LoadMap(const int arr[20][25]);
    void DrawMap();
private:

    SDL_FRect SourceRect, DestinationRect;

    //@TODO TEmp

    SDL_Texture* Dirt = nullptr;
    SDL_Texture* Grass = nullptr;
    SDL_Texture* Water = nullptr;

    int map[20][25];
};
