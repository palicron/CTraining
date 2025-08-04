#pragma once
#include <SDL3/SDL_rect.h>

#include "../Framework/EntityComponentSystem.h"


class TransformComponent;

class ColliderComponent: public Component
{
public:
    ColliderComponent(const std::string& tag);
    ~ColliderComponent() override = default;
    SDL_FRect collider;
    std::string Tag;

    TransformComponent* OwnerTransform;

    void ComponentInit() override;

    void ComponentUpdate() override;
};
