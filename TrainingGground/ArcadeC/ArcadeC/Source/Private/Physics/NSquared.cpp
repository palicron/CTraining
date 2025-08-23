#include "../../Public/Physics/NSquared.h"

NSquared::NSquared()
{
}

NSquared::~NSquared()
{
}

void NSquared::Add(ColliderComponent* Component)
{
    CollidersList.push_back(Component);
}

void NSquared::Remove(ColliderComponent* Component)
{
    uint32_t index = 0;
    for (const ColliderComponent* CurrentComponent : CollidersList)
    {
        if (CurrentComponent == Component)
        {
            CollidersList.erase(CollidersList.begin() + index);
            break;
        }
    }
}

void NSquared::Update()
{
}

const ColliderPairList& NSquared::ComputePairs()
{
    ColliderPairs.clear();

    auto end = CollidersList.end();

    for (auto i = CollidersList.begin(); i != end; ++i)
    {
        auto jStart = i;
        for (auto j = ++jStart; j != end; ++j)
        {
            ColliderComponent* ColliderA = *i;
            ColliderComponent* ColliderB = *j;

            if (ColliderA == ColliderB)
            {
                continue;
            }

            if (ColliderA->Collides(ColliderB))
            {
                ColliderPairs.emplace_back(ColliderA, ColliderB);
            }
        }
    }

    return ColliderPairs;
}

ColliderComponent* NSquared::Pick(const Vector2D& point) const
{
    for (ColliderComponent* Comp : CollidersList)
    {
        if (Comp->Collides(point))
        {
            return Comp;
        }
    }
}

void NSquared::Query(const ColliderComponent& Collider, ColliderList& Results) const
{
    for (ColliderComponent* Comp : CollidersList)
    {
        if (Comp->Collides(&Collider))
        {
            Results.emplace_back(Comp);
        }
    }
}

RayCastResult NSquared::RayCast2D(const Ray2& ray) const
{

    //@TODO Implement
    typedef std::vector<ColliderComponent*> ColliderList;

    ColliderList candidatesList;
    candidatesList.reserve(CollidersList.size());
    return RayCastResult();
}

std::vector<ColliderComponent*> NSquared::GetColliders() const
{
    return CollidersList;
}


