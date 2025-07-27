#include "../../Public/Components/TransformComponent.h"

TransformComponent::TransformComponent()
{
    Position = Vector2D::ZeroVector();
}

TransformComponent::TransformComponent(const Vector2D& position):Component(),Position(position)
{
    
}

TransformComponent::TransformComponent(const float x, const float y)
{
    Position = Vector2D(x,y);
}

TransformComponent::TransformComponent(const int32_t x, const int32_t y)
{
  Position = Vector2D(x,y);
}

TransformComponent::~TransformComponent()
{
    Component::~Component();
}

void TransformComponent::SetPosition(const Vector2D NewPosition)
{
    Position = NewPosition;
}

void TransformComponent::SetPosition(const int32_t x, const int32_t y)
{
    Position = Vector2D(x,y);
}

void TransformComponent::ComponentUpdate()
{
    Component::ComponentUpdate();
    Position++;
}
