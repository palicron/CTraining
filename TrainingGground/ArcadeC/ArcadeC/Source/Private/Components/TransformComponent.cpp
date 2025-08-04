#include "../../Public/Components/TransformComponent.h"

TransformComponent::TransformComponent()
{
    Position = Vector2D::ZeroVector();
    Scale = Vector2D(1.f);
    Size = Vector2D(32.f);
}

TransformComponent::TransformComponent(const Vector2D& position):Component(),Position(position)
{
    
}

TransformComponent::TransformComponent(const Vector2D& position, const Vector2D& size, const Vector2D& scale):Component(),Position(position),Size(size),Scale(scale)
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
}
