#include "../../Public/Components/MovementComponent.h"

#include "../../Public/Components/TransformComponent.h"

MovementComponent::MovementComponent():Component()
{
    Velocity = Vector2D::ZeroVector();
    Speed = 2.f;
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
}

void MovementComponent::Move(const Vector2D& Direction)
{
    if (OwnerTransform)
    {
        OwnerTransform->SetPosition(OwnerTransform->GePosition() + Direction);
    }
}

void MovementComponent::AddInputVector(const Vector2D& Direction)
{
    
}
