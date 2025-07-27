
#include "../../Public/Actors/Actor.h"

#include <iostream>
#include <SDL3/SDL_oldnames.h>
#include <SDL3/SDL_render.h>
#include "../../Public/Managers/TextureManager.h""
Actor::Actor(const char* name, const char* texturePath, SDL_Renderer* inRenderer,const int x, const int y): Name(name), TexturePath(texturePath), Xpos(x), Ypos(y)
{
    Renderer = inRenderer ;
    Texture = TextureManager::LoadTexture(TexturePath);
}

Actor::~Actor()
{
}

void Actor::Update()
{
    SourceRect.h = 25;
    SourceRect.w = 25;
    SourceRect.x = 0;
    SourceRect.y = 0;

    DestinationRect.x = Xpos;
    DestinationRect.y = Ypos;
    DestinationRect.h = SourceRect.h;
    DestinationRect.w = SourceRect.w;
}

void Actor::Render()
{
    if (!Renderer || !Texture)
    {
        std::cout << "Renderer or Texture is null in Actor : " << Name << '\n';
        return;
    }
    SDL_RenderTexture(Renderer,Texture,&SourceRect,&DestinationRect);
}
