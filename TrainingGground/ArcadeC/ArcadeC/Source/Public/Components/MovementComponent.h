#pragma once
#include "../Framework/EntityComponentSystem.h"
#include "../Math/Vector2D.h"


class TransformComponent;

class MovementComponent: public Component
{
public:
    
    MovementComponent();
    ~MovementComponent() override = default;
    void ComponentInit() override;
    void ComponentUpdate() override;

    virtual void Move(const Vector2D& Direction);

protected:

    Vector2D VelocityDirection;
    float Speed;

    float MaxSpeed;
    float Acceleration;
    float Deceleration;
    
    virtual void MoveInternal();
    virtual void Accelerate();
    virtual void Decelerate();
    TransformComponent* OwnerTransform;
    
};


