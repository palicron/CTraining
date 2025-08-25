#include <algorithm>

#include "../../Public/Components/MovementComponent.h"

#include "../../Public/Components/TransformComponent.h"
#include "../../Public/Math/Math.h"

MovementComponent::MovementComponent():Component()
{
    VelocityDirection = Vector2D::ZeroVector();
    Speed = 2.f;
    MaxSpeed = 10.f;
    Acceleration = 0.02f;
    Deceleration = 0.5f;
    //@TODO Entiy should init his componets
}

void MovementComponent::ComponentInit()
{
    Component::ComponentInit();
    if (!Owner)
    {
        std::cout << "Owner is null in MovementComponent" << '\n';
        return;
    }

    OwnerTransform = &Owner->GetComponent<TransformComponent>();
}

void MovementComponent::ComponentUpdate()
{
    Component::ComponentUpdate();

    //@TODO this is a simpe move
    if (VelocityDirection.IsNearEqualZero())
    {
        Decelerate();
    }
    else
    {
        Accelerate();
    }

    MoveInternal();

}

void MovementComponent::Move(const Vector2D& Direction)
{
    VelocityDirection = Direction;
    VelocityDirection = Math::NormalizeVector2DAndClamp(VelocityDirection, -1.f, 1.f);
    

}

void MovementComponent::MoveInternal()
{
    //TODO: Check COllison / Aceleartion ETC
    if (OwnerTransform)
    {
        OwnerTransform->SetPosition(OwnerTransform->GePosition() + (VelocityDirection * Speed));
    }
}

void MovementComponent::Accelerate()
{
    //@Todo firt implementation
    Speed += Acceleration;
    Speed = std::min(Speed, MaxSpeed);
}

void MovementComponent::Decelerate()
{
    //@Todo firt implementation
    Speed -= Acceleration;
    Speed = std::max(Speed, 0.f);
}
