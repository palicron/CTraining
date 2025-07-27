#pragma once
#include <memory>
#include <SDL3/SDL_render.h>
#include "../Framework/EntityComponentSystem.h"
class SceneComponent;

class SpriteComponent: public Component
{
    
public:

    SpriteComponent();
    SpriteComponent(const char* texturePath,const float inSizeX = 1.f, const float inSizeY = 1.f);
    ~SpriteComponent() = default;

    virtual void ComponentInit() override;
    virtual void ComponentUpdate() override;
    virtual void ComponentDraw() override;

    void SetTexture(const char* texturePath);
    
private:
    SceneComponent* SceneComponent;

    SDL_Texture* Texture;
    SDL_FRect SourceRect, DestinationRect;

    float SizeX, SizeY;
    
    
};
