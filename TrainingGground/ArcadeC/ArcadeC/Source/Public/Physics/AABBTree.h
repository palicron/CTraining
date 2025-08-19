#pragma once
#include "Broadphase.h"

typedef std::vector<Node*> NodeList;

class AABBTree: public Broadphase
{
public:

    void Add(ColliderComponent* Component) override;

    void Remove(ColliderComponent* Component) override;
    
    void Update() override;
    
    const ColliderPairList& ComputePairs() override;
    
    ColliderComponent* Pick(const Vector2D& point) const override;
    
    void Query(const ColliderComponent& Collider, ColliderList& Results) const override;
    
    RayCastResult RayCast2D(const Ray2& ray) const override;

private:
    
    Node* Root;
    ColliderPairList Pairs;
    float margin;
    NodeList InvalidNodes;

    void UpdateNodeHelper(Node* node, NodeList& invalidNodes);
    void InsertNode(Node* node, Node** parent);
    void RemoveNode(Node* node);
    void ComputePairsHelper(Node* node, Node* other);
    void ClearChildrenCrossFlagHelper(Node* node);
    void CrossChildren(Node* node);
};
