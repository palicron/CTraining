#pragma once
#include <memory>
#include <SDL3/SDL_render.h>

struct SDL_Renderer;

//TODO: Move al think about textures and renderes to a component whent the engine ahs compenents
class Actor
{
public:
    
    Actor(const char* name, const char* texturePath, SDL_Renderer* inRenderer,const int x, const int y);
    ~Actor();

    void Update();
    void Render();
private:

    
    const char* Name;
    const char* TexturePath;

    SDL_Renderer* Renderer;
    
    int Xpos;
    int Ypos;

    SDL_Texture* Texture;
    SDL_FRect SourceRect, DestinationRect;
};
