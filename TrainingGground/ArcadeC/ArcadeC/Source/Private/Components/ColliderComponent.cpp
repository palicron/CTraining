#include "../../Public/Components/ColliderComponent.h"

#include <SDL3/SDL_render.h>

#include "../../Public/Collision.h"
#include "../../Public/Game.h"
#include "../../Public/Components/TransformComponent.h"
#include "../../Public/Definitions/PhysicsDefinitions.h"

ColliderComponent::ColliderComponent(const std::string& tag): Tag(tag), OwnerTransform(nullptr)
{
    bShowDebugBox = true;
    Collider = std::make_unique<AABBCollider>();
}

ColliderComponent::~ColliderComponent()
{
    Collider.reset();
}

void ColliderComponent::ComponentInit()
{
    Component::ComponentInit();
    if (!Owner)
    {
        std::cout << "Owner is null in ColliderComponent" << '\n';
        return;
    }
    if (!Owner->HasComponent<TransformComponent>())
    {
        std::cout << "Owner Dont Have TransformComponent Creating One" << '\n';
        OwnerTransform = &Owner->addComponent<TransformComponent>();return;
    }
    else
    {
        OwnerTransform = &Owner->GetComponent<TransformComponent>();
    }
    if (Collider)
    {
        Collider->MinPoint = OwnerTransform->GetScale();
        Collider->MaxPoint = OwnerTransform->GetScaleSize() + Collider->MinPoint;
    }
}

void ColliderComponent::ComponentUpdate()
{
    if (!OwnerTransform || !Collider)
    {
        return;
    }

    Collider->UpdateAABBWorldPosition(OwnerTransform->GePosition());
}

void ColliderComponent::ComponentDraw()
{
    Component::ComponentDraw();

    SDL_FRect DebugBox;
    const std::vector<Vector2D> CollisionPosition = Collider->GetWorldPosition();
    

    DebugBox.x = CollisionPosition[0].x;
    DebugBox.y = CollisionPosition[0].y;
    DebugBox.w = CollisionPosition[1].x - CollisionPosition[0].x;
    DebugBox.h = CollisionPosition[1].y - CollisionPosition[0].y;
    
    SDL_SetRenderDrawColor(Game::GetRenderer(), 0, 0, 255
        , SDL_ALPHA_OPAQUE);
    SDL_RenderRect(Game::GetRenderer(), &DebugBox);
   
}

bool ColliderComponent::Collides(const Vector2D& point) const
{
    return Collider->Collides(point);
}

void ColliderComponent::OnCollision(ColliderComponent* other)
{
    if (OwnerTransform)
    {
        OwnerTransform->SetTransformTolLastPosition();
    }

  
   // OnCollisionDelegate.Execute(this, other);
    
}

bool ColliderComponent::Collides(const ColliderComponent* other) const
{
    return Collider->Collides(other->Collider.get());
}
