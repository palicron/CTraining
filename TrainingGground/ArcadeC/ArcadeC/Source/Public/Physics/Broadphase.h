#pragma once
#include <utility>
#include <list>
#include "../../Public/Components/ColliderComponent.h"
#include "../Definitions/PhysicsDefinitions.h"


typedef std::pair<ColliderComponent*, ColliderComponent*> ColliderPair;
typedef std::list<ColliderPair> ColliderPairList;
typedef std::vector<ColliderComponent*> ColliderList;

//@TODO im using Collider component but this shoudl be generic aabb class for multiple implementations
class Broadphase
{
public:
    virtual ~Broadphase() = default;
    // adds a new AABB to the broadphase
    virtual void Add(ColliderComponent* Component) = 0;

    virtual void Remove(ColliderComponent* Component) = 0;
    
    // updates broadphase to react to changes to AABB
    virtual void Update() = 0;

    // returns a list of possibly colliding colliders
    virtual const ColliderPairList& ComputePairs() = 0;

    // returns a collider that collides with a point
    // returns null if no such collider exists
    virtual ColliderComponent* Pick(const Vector2D& point) const = 0;

    // returns a list of colliders whose AABBs collide 
    // with a query AABB
    virtual void Query(const ColliderComponent& Collider, ColliderList& Results) const = 0;

    // result contains the first collider the ray hits
    // result contains null if no collider is hit
    virtual RayCastResult RayCast2D(const Ray2& ray) const = 0;
};
