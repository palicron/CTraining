#pragma once
#include "../Framework/EntityComponentSystem.h"
#include "../Math/Vector2D.h"


class TransformComponent : public Component
{
public:

    TransformComponent();
    TransformComponent(const Vector2D& position);
    TransformComponent(const float x, const float y);
    TransformComponent(const int32_t x, const int32_t y);
    ~TransformComponent() override;

    float GetX() const { return Position.x; }
    float GetY() const { return Position.y; }

    void SetPosition(const Vector2D NewPosition);
    void SetPosition(const int32_t x, const int32_t y);

    void ComponentUpdate() override;

    Vector2D GePosition() const { return Position; }
private:

    //TODO Changt to vecto2d
    Vector2D Position;
    
};
