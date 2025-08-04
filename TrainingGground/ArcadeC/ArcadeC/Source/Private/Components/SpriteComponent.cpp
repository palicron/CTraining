#include "../../Public/Components/SpriteComponent.h"

#include "../../Public/Components/TransformComponent.h"
#include "../../Public/Managers/TextureManager.h"

SpriteComponent::SpriteComponent():Texture(nullptr)
{
    
}

SpriteComponent::SpriteComponent(const char* texturePath,const float inSizeX , const float inSizeY)
{
    SetTexture(texturePath);
    DestinationRect.x = SourceRect.x = inSizeX;
    DestinationRect.y = SourceRect.y = inSizeY;
    DestinationRect.w = SourceRect.w = 32;
    DestinationRect.h = SourceRect.h = 32;
}

SpriteComponent::~SpriteComponent()
{
    SDL_DestroyTexture(Texture);
}

void SpriteComponent::ComponentInit()
{
    Component::ComponentInit();
    if (Owner)
    {
        TransformComponent = &Owner->GetComponent<class TransformComponent>();
    }

    if (TransformComponent)
    {
        SourceRect.w = TransformComponent->GetScale().x;
        SourceRect.h = TransformComponent->GetScale().y;
        DestinationRect.w = TransformComponent->GetScaleSize().x;
        DestinationRect.h = TransformComponent->GetScaleSize().y;
    }

}

void SpriteComponent::ComponentUpdate()
{
    Component::ComponentUpdate();
    DestinationRect.x = TransformComponent->GetX();
    DestinationRect.y = TransformComponent->GetY();
}

void SpriteComponent::ComponentDraw()
{
    Component::ComponentDraw();
    if (Texture)
    {
        TextureManager::Draw(Texture,&SourceRect,&DestinationRect);
    }

}

void SpriteComponent::SetTexture(const char* texturePath)
{
    Texture = TextureManager::LoadTexture(texturePath);
}
