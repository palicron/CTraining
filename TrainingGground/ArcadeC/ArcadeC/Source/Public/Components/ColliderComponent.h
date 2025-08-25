#pragma once
#include <SDL3/SDL_rect.h>
#include "../Framework/EntityComponentSystem.h"
#include "../utility/Delegates.h"

class Vector2D;
struct AABBCollider;
class TransformComponent;


class ColliderComponent: public Component
{
public:
    
    ColliderComponent(const std::string& tag);
    ~ColliderComponent() override;

    std::unique_ptr<AABBCollider> Collider;
    std::string Tag;

    TransformComponent* OwnerTransform;

    void ComponentInit() override;

    void ComponentUpdate() override;

    void ComponentDraw() override;

    bool Collides(const ColliderComponent* other) const;

    bool Collides(const Vector2D& point) const;

    //@TODO TEmpora collision
    void OnCollision(ColliderComponent* other);
    
  
    //Delegates<void(ColliderComponent* /* This Collider */, ColliderComponent*/*Other*/)> OnCollisionDelegate;

protected:

    bool bShowDebugBox;
};
