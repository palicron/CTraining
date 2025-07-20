#include "../../Public/Components/SceneComponent.h"

SceneComponent::SceneComponent()
{
    X = 0.f;
    Y = 0.f;
}

SceneComponent::SceneComponent(const float x, const float y):Component(),X(0.f),Y(0.f)
{
    
}

SceneComponent::SceneComponent(const int32_t x, const int32_t y)
{
    X = static_cast<float>(x);
    Y = static_cast<float>(y);
}

SceneComponent::~SceneComponent()
{
    Component::~Component();
}

void SceneComponent::SetPosition(const float x, const float y)
{
    X = x;
    Y = y;
}

void SceneComponent::SetPosition(const int32_t x, const int32_t y)
{
    X = static_cast<float>(x);
    Y = static_cast<float>(y);
}

void SceneComponent::ComponentUpdate()
{
    Component::ComponentUpdate();
    X++;
    Y++;
}
