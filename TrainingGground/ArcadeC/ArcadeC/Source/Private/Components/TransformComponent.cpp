#include "../../Public/Components/TransformComponent.h"

TransformComponent::TransformComponent()
{
    Position = Vector2D::ZeroVector();
    Scale = Vector2D(1.f);
    Size = Vector2D(32.f);
}

TransformComponent::TransformComponent(const Vector2D& position):Component(),Position(position)
{
    LastPosition = Position;
}

TransformComponent::TransformComponent(const Vector2D& position, const Vector2D& size, const Vector2D& scale) : Component(), Position(position), Size(size), Scale(scale)
{
    LastPosition = Position;
}

TransformComponent::TransformComponent(const float x, const float y)
{
    Position = Vector2D(x, y);
    LastPosition = Position;
}

TransformComponent::TransformComponent(const int32_t x, const int32_t y)
{
    Position = Vector2D(x, y);
    LastPosition = Position;
}

TransformComponent::~TransformComponent()
{
    Component::~Component();
}

void TransformComponent::SetPosition(const Vector2D NewPosition)
{
    LastPosition = Position;
    Position = NewPosition;
}

void TransformComponent::SetPosition(const int32_t x, const int32_t y)
{
    LastPosition = Position;
    Position = Vector2D(x, y);
}

void TransformComponent::ComponentUpdate()
{
}

void TransformComponent::SetTransformTolLastPosition()
{
    Position = LastPosition;
}
