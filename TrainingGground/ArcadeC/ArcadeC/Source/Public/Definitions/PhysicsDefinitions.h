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

    Vector2D MinSize;
    Vector2D MaxSize;
    
    Vector2D CurrentPosition;
    
    std::vector<Vector2D> GetCorners() const
    {
        std::vector<Vector2D> corners;
        corners.push_back(MinPoint);
        corners.push_back(MinPoint + Vector2D(MaxPoint.x, MinPoint.y));
        corners.push_back(MinPoint + Vector2D(MinPoint.x, MaxPoint.y));
        corners.push_back(MaxPoint);
        return corners;
    }

    std::vector<Vector2D> GetWorldPosition() const
    {
        std::vector<Vector2D> corners;
        corners.push_back(MinPoint + CurrentPosition);
        corners.push_back(MaxPoint + CurrentPosition);

        return corners;
    }

    AABBCollider Union(const AABBCollider& otherCollider) const
    {

        //@TODO weird need to revisit this AABB collisions
        std::vector<Vector2D> corners = GetWorldPosition();
        std::vector<Vector2D> OtherCorners = otherCollider.GetWorldPosition();
        const Vector2D MinUnionPoint(std::min(corners[0].x, OtherCorners[0].x), std::min(corners[0].y, OtherCorners[0].y));
        const Vector2D MaxUnionPoint(std::max(corners[1].x, OtherCorners[1].x), std::max(corners[1].y, OtherCorners[1].y));

        return AABBCollider(MinUnionPoint, MaxUnionPoint);
    }

    bool Contains (const AABBCollider* Other)
    {
        if (!Other)
        {
            return false;       
        }
        
        std::vector<Vector2D> corners = GetWorldPosition();
        std::vector<Vector2D> OtherCorners = Other->GetWorldPosition();
        //@TODO fast check if this contain the other aabb box calculation no rotation

        
        const bool MinxCollision = corners[1].x > OtherCorners[0].x;
        const bool MaxxCollision = OtherCorners[1].x  > corners[0].x;
        const bool MinyCollision = corners[1].y >= OtherCorners[0].y;
        const bool MaxyCollision = OtherCorners[1].y > corners[0].y;
        return MinxCollision && MaxxCollision && MinyCollision && MaxyCollision;
    }

    bool Collides(const AABBCollider* Other) const
    {
        if (!Other)
        {
            return false;       
        }

        std::vector<Vector2D> corners = GetWorldPosition();
        std::vector<Vector2D> OtherCorners = Other->GetWorldPosition();
        //@TODO fast check if this contain the other aabb box calculation no rotation

        
        const bool MinxCollision = corners[1].x >= OtherCorners[0].x;
        const bool MaxxCollision = OtherCorners[1].x  >= corners[0].x;
        const bool MinyCollision = corners[1].y >= OtherCorners[0].y;
        const bool MaxyCollision = OtherCorners[1].y >= corners[0].y;
        return MinxCollision && MaxxCollision && MinyCollision && MaxyCollision;
        
    }

    void UpdateAABBWorldPosition(const Vector2D& inPosition)
    {
        CurrentPosition = inPosition;
    }

    bool Collides(const Vector2D& Other) const
    {
        return (MinPoint.x <= Other.x && MaxPoint.x >= Other.x) && (MinPoint.y <= Other.y && MaxPoint.y >= Other.y);
    }
    
    AABBCollider():MinPoint(Vector2D::ZeroVector()),MaxPoint(Vector2D::ZeroVector())
    {
    }

    AABBCollider(const Vector2D& inMinPoint, const Vector2D& inMaxPoint):MinPoint(inMinPoint),MaxPoint(inMaxPoint)
    {
    }

    float Area() const
    {
        return (MaxPoint.x - MinPoint.x) * (MaxPoint.y - MinPoint.y);
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
            Collider = Children[0]->Collider.Union(Children[1] ? Children[1]->Collider : AABBCollider());
        }
    }

    bool Collides(const ColliderComponent* Other)
    {
        if (!Other)
        {
            return false;
        }

        return Collider.Collides(Other->Collider.get());
    }
    
    Node* GetSibling() const
    {
        return this == Parent->Children[0] ? Parent->Children[1] : Parent->Children[0];
    }
};