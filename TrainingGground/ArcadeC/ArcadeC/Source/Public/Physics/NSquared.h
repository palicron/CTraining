#pragma once
#include "Broadphase.h"

class NSquared : public Broadphase
{
    
public:
    
    void Add(ColliderComponent* Component) override;
    void Remove(ColliderComponent* Component) override;
    void Update() override;
    const ColliderPairList& ComputePairs() override;
    ColliderComponent* Pick(const Vector2D& point) const override;
    void Query(const ColliderComponent& Collider, ColliderList& Results) const override;
    RayCastResult RayCast2D(const Ray2& ray) const override;
};
