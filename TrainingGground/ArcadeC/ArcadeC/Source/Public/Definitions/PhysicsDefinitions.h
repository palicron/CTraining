#pragma once
#include <vector>
#include "../Components/ColliderComponent.h"
#include "../Math/Vector2D.h"




struct Ray2
{
    Vector2D Position;
    Vector2D Direction;

    Ray2():Position(Vector2D::ZeroVector()),Direction(Vector2D::ZeroVector()){}
    Ray2(const Vector2D& inPosition, const Vector2D& inDirection):Position(inPosition)
    {
        Direction = inDirection.GetSafeNormal();
    }
};

struct RayCastResult
{
    bool bHit;
    ColliderComponent* HitCollider;
    Vector2D HitPoint;
    Vector2D HitNormal;

    RayCastResult(): bHit(false), HitCollider(nullptr)
    {
    }
};

//For the momenot this just take in account square Collision
struct AABBCollider
{
    Vector2D MinPoint;
    Vector2D MaxPoint;

    std::vector<Vector2D> GetCorners() const
    {
        std::vector<Vector2D> corners;
        corners.push_back(MinPoint);
        corners.push_back(MinPoint + Vector2D(MaxPoint.x, MinPoint.y));
        corners.push_back(MinPoint + Vector2D(MinPoint.x, MaxPoint.y));
        corners.push_back(MaxPoint);
        return corners;
    }

    std::vector<Vector2D> GetWorldPosition(const Vector2D& OwnerPosition)
    {
        std::vector<Vector2D> corners;
        corners.push_back(MinPoint + OwnerPosition);
        corners.push_back(MaxPoint + OwnerPosition);

        return corners;
    }

    AABBCollider Union(const AABBCollider& otherCollider) const
    {
        const Vector2D MinUnionPoint(std::min(MinPoint.x, otherCollider.MinPoint.x), std::min(MinPoint.y, otherCollider.MinPoint.y));
        const Vector2D MaxUnionPoint(std::max(MaxPoint.x, otherCollider.MaxPoint.x), std::max(MaxPoint.y, otherCollider.MaxPoint.y));

        return AABBCollider(MinUnionPoint, MaxUnionPoint);
    }
    
    AABBCollider():MinPoint(Vector2D::ZeroVector()),MaxPoint(Vector2D::ZeroVector())
    {
    }

    AABBCollider(const Vector2D& inMinPoint, const Vector2D& inMaxPoint):MinPoint(inMinPoint),MaxPoint(inMaxPoint)
    {
    }

   
};

struct Node
{
    Node* Parent;
    Node* Children[2];

    bool childrenCrossed;
    ColliderComponent* Data;
    AABBCollider Collider;

    bool IsLeaf() const { return Children[0] == nullptr && Children[1] == nullptr; }
    bool IsRoot() const { return Parent == nullptr; }

    void SetBranch(Node* Left = nullptr, Node* Right = nullptr)
    {
        if (Left)
        {
            Left->Parent = this;
        }
        if (Right)
        {
            Right->Parent = this;       
        }
        Children[0] = Left;
        Children[1] = Right;
    }

    void SetLeaf(ColliderComponent* Data)
    {
        this->Data = Data;
        //@TODO add ust data toi collider
        SetBranch();
    }

    void UpdateAABB(float margin)
    {
        if (IsLeaf())
        {
            const Vector2D marginVec(margin);
            Collider.MinPoint = Data->Collider->MinPoint - marginVec;
            Collider.MaxPoint = Data->Collider->MaxPoint + marginVec;
        }
        else
        {
            Collider = Children[0]->Collider.Union(Children[1]->Collider);
        }
    }
};