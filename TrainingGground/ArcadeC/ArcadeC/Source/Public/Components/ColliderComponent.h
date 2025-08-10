#pragma once
#include <SDL3/SDL_rect.h>
#include "../Framework/EntityComponentSystem.h"

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

protected:

    bool bShowDebugBox;
};
