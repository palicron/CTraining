#pragma once
#include "../Framework/EntityComponentSystem.h"
#include "../Math/Vector2D.h"


class TransformComponent : public Component
{
public:

    //TODO : amve this i shoudl crete a Struct of trasform to save thepositions
    TransformComponent();
    TransformComponent(const Vector2D& position);
    TransformComponent(const Vector2D& position,const Vector2D& size,const Vector2D& scale = Vector2D(1.f));
    TransformComponent(const float x, const float y);
    TransformComponent(const int32_t x, const int32_t y);
    ~TransformComponent() override;

    float GetX() const { return Position.x; }
    float GetY() const { return Position.y; }

    void SetPosition(const Vector2D NewPosition);
    void SetPosition(const int32_t x, const int32_t y);

    void ComponentUpdate() override;

    Vector2D GePosition() const { return Position; }
    Vector2D GetScale() const { return Scale; }
    Vector2D GetSize() const{return Size;}
    Vector2D GetScaleSize() const { return Size * Scale; }
    
    void SetScale(const Vector2D NewScale) { Scale = NewScale; }

private:
    
    Vector2D Position;
    Vector2D Scale;
    Vector2D Size;
    
};
