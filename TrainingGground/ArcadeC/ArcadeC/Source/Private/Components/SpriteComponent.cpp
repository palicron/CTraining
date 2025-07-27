#include "../../Public/Components/SpriteComponent.h"

#include "../../Public/Components/SceneComponent.h"
#include "../../Public/Managers/TextureManager.h"

SpriteComponent::SpriteComponent():Texture(nullptr)
{
}

SpriteComponent::SpriteComponent(const char* texturePath,const float inSizeX , const float inSizeY ):SizeX(inSizeX),SizeY(inSizeY)
{
    SetTexture(texturePath);
    DestinationRect.x = SourceRect.x = inSizeX;
    DestinationRect.y = SourceRect.y = inSizeY;
    DestinationRect.w = SourceRect.w = 32;
    DestinationRect.h = SourceRect.h = 32;
}

void SpriteComponent::ComponentInit()
{
    Component::ComponentInit();
    if (Owner)
    {
        SceneComponent = &Owner->GetComponent<class SceneComponent>();
    }

}

void SpriteComponent::ComponentUpdate()
{
    Component::ComponentUpdate();
    DestinationRect.x = SceneComponent->GetX();
    DestinationRect.y = SceneComponent->GetY();
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
