#include "../../Public/Components/ColliderComponent.h"
#include "../../Public/Components/TransformComponent.h"

ColliderComponent::ColliderComponent(const std::string& tag): collider(), Tag(tag), OwnerTransform(nullptr)
{
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
}

void ColliderComponent::ComponentUpdate()
{
    if (!OwnerTransform)
    {
        return;
    }
    //TODO Check CAst
    collider.x = static_cast<int>(OwnerTransform->GePosition().x);
    collider.y = static_cast<int>(OwnerTransform->GePosition().y);
    collider.w = static_cast<int>(OwnerTransform->GetScaleSize().x);
    collider.h = static_cast<int>(OwnerTransform->GetScaleSize().y);
}
