#include "../../Public/Physics/AABBTree.h"

#include <queue>

void AABBTree::Add(ColliderComponent* Component)
{
    if (Root)
    {
        Node* node = new Node();
        node->SetLeaf(Component);
        node->UpdateAABB(margin);
        InsertNode(node, &Root);
    }
    else
    {
        Root = new Node();
        Root->SetLeaf(Component);
        Root->UpdateAABB(margin);
    }
}

void AABBTree::Remove(ColliderComponent* Component)
{
    //@TODO mmm I miisin dome function in Coliders need the aabb to now his node 

}

void AABBTree::Update()
{
    if (!Root)
    {
        return;
    }

    InvalidNodes.clear();
    UpdateNodeHelper(Root, InvalidNodes);

    for (Node* node : InvalidNodes)
    {
        Node* parent = node->Parent;
        Node* sibiling = node->GetSibling();
        Node** ParentLink = parent->Parent
                                ? (parent == parent->Parent->Children[0]
                                       ? &parent->Parent->Children[0]
                                       : &parent->Parent->Children[1])
                                : &Root;

        sibiling->Parent = parent->Parent;
        *ParentLink = sibiling;
        delete parent;

        node->UpdateAABB(margin);
        InsertNode(node, &Root);
    }

    InvalidNodes.clear();
}

const ColliderPairList& AABBTree::ComputePairs()
{
    Pairs.clear();

    if (!Root || Root->IsLeaf())
    {
        return Pairs;
    }
    ClearChildrenCrossFlagHelper(Root->Children[0]);
    ClearChildrenCrossFlagHelper(Root->Children[1]);

    ComputePairsHelper(Root->Children[0], Root->Children[1]);

    return Pairs;
}

ColliderComponent* AABBTree::Pick(const Vector2D& point) const
{
    std::queue<Node*> q;
    if (Root)
    {
        q.push(Root);
    }

    while (!q.empty())
    {
        Node& node = *q.front();
        q.pop();
        if (node.IsLeaf())
        {
            if (node.Data->Collides(point))
            {
                return node.Data;
            }
        }
        else
        {
            //TODO: prob i coauld check if the point is in teh union of this is not i simple can no continue 
            if (node.Children[0])
            {
                q.push(node.Children[0]);
            }
            if (node.Children[1])
            {
                q.push(node.Children[1]);
            }
        }
    }
}

void AABBTree::Query(const ColliderComponent& Collider, ColliderList& Results) const
{
}

RayCastResult AABBTree::RayCast2D(const Ray2& ray) const
{
    return RayCastResult();
}

void AABBTree::UpdateNodeHelper(Node* node, NodeList& invalidNodes)
{
    if (node && node->IsLeaf())
    {
        if (!node->Collider.Contains(node->Data->Collider.get()))
        {
            invalidNodes.push_back(node);
        }
    }
    else
    {
        UpdateNodeHelper(node->Children[0], invalidNodes);
        UpdateNodeHelper(node->Children[1], invalidNodes);
    }   
}

void AABBTree::InsertNode(Node* node, Node** parent)
{
    Node* p = *parent;

    if (p && p->IsLeaf())
    {
        Node* newParent = new Node();
        newParent->Parent = p->Parent;
        newParent->SetBranch(node, p);
        *parent = newParent;
        return;
    }


    //Calculation to balance tree base on less Area of the New Collider
    const AABBCollider* aabb0 = &p->Children[0]->Collider;
    const AABBCollider* aabb1 = &p->Children[1]->Collider;

    const float volumeDiff0 = aabb0->Union(node->Collider).Area() - aabb0->Area();
    const float volumeDiff1 = aabb1->Union(node->Collider).Area() - aabb1->Area();

    if (volumeDiff0 < volumeDiff1)
    {
        InsertNode(node, &p->Children[0]);
    }
    else
    {
        InsertNode(node, &p->Children[1]);
    }
    // update parent AABB
    // (propagates back up the recursion stack)
    (*parent)->UpdateAABB(margin);
}

void AABBTree::RemoveNode(Node* node)
{
    Node* parent = node->Parent;
    if (parent)
    {
        Node* sibiling = node->GetSibling();
        if (parent->Parent)
        {
            //Update links
            sibiling->Parent = parent->Parent;
            (parent == parent->Parent->Children[0] ? parent->Parent->Children[0] : parent->Parent->Children[1]) = sibiling;
        }
        else
        {
            Node* sibiling = node->GetSibling();
            Root = sibiling;
            sibiling->Parent = nullptr;
        }

        delete node;
        delete parent;
        return;
    }

    Root = nullptr;
    delete node;
}

void AABBTree::ComputePairsHelper(Node* node, Node* other)
{
    if (node->IsLeaf())
    {
        if (other->IsLeaf())
        {
            //Case 2 leaf, check for real collision
            if (node->Data->Collides(node->Data))
            {
                Pairs.emplace_back(std::make_pair(node->Data, other->Data));
            }
        }
        else
        {
            //Case 1 branch 1 leach , 2 cross checks
            CrossChildren(other);
            ComputePairsHelper(node,other->Children[0]);
            ComputePairsHelper(node,other->Children[1]);
        }
    }
    else
    {
        if (other->IsLeaf())
        {
            CrossChildren(node);
            ComputePairsHelper(node->Children[0], other);
            ComputePairsHelper(node->Children[1], other);
        }
        else
        {
            CrossChildren(node);
            CrossChildren(other);
            ComputePairsHelper(node->Children[0], other->Children[0]);
            ComputePairsHelper(node->Children[0], other->Children[1]);
            ComputePairsHelper(node->Children[1], other->Children[0]);
            ComputePairsHelper(node->Children[1], other->Children[1]);
        }
    }
}

void AABBTree::ClearChildrenCrossFlagHelper(Node* node)
{
    if (!node)
    {
        return;
    }

    node->childrenCrossed = false;
    if (!node->IsLeaf())
    {
        ClearChildrenCrossFlagHelper(node->Children[0]);
        ClearChildrenCrossFlagHelper(node->Children[1]);
    }
}

void AABBTree::CrossChildren(Node* node)
{
    if (node && !node->childrenCrossed)
    {
        ComputePairsHelper(node->Children[0], node->Children[1]);
        node->childrenCrossed = true;
    }
}
