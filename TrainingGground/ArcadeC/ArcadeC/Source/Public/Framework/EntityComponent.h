#pragma once
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;

using ComponentID = std::size_t;

inline ComponentID GetComponentTypeID()
{
    static ComponentID ID = 0;
    return ID++;
}

template <typename T>
inline ComponentID GetComponentTypeID() noexcept
{
    static ComponentID TypeID = GetComponentTypeID();
    return TypeID;
}

constexpr std::size_t maxComponents = 32;

using ComponentBitSet = std::bitset<maxComponents>;
using ComponentArray = std::array<std::unique_ptr<Component>, maxComponents>;

class Component
{
public:
    
    Component();
    virtual ~Component();

    virtual void ComponentInit() {}

    virtual void ComponentUpdate() {}

    virtual void ComponentDraw() {}

    void SetOwner(Entity* NewOwner) { Owner = NewOwner; }
protected:
    Entity* Owner;
    
};

class Entity
{
public:

    bool IsActive() const { return bActive;}

    void SetActive(bool active) { bActive = active; }

    void update()
    {
        for (auto& Component : Components)
        {
            Component->ComponentUpdate();
            Component->ComponentDraw();
        }
    }

    void Draw(){}

    void Destroy()
    {
        bActive = false; 
    }

    
    template<typename T> bool HasComponent() const
    {
        return ComponentBitSet.test(GetComponentTypeID<T>());
    }

    template<typename T, typename ... TArgs>
    T& addComponent(TArgs&&... mArgs)
    {
        std::unique_ptr<T> c = std::make_unique<T>(std::forward<TArgs>(mArgs)...);
        T* RawPtr = c.get();
        RawPtr->entity = this;

        Components.emplace_back(std::move(c));
        ComponentArray[GetComponentTypeID()] = c;
        ComponentBitSet[GetComponentTypeID()] = true;
        c->ComponentInit();
        return *RawPtr;
    }

    template<typename T> T& GetComponent() const
    {
        return *static_cast<T*>(ComponentArray[GetComponentTypeID<T>()].get());
    }
private:
    
    bool bActive = true;

    std::vector<std::unique_ptr<Component>> Components;

    ComponentArray ComponentArray;

    ComponentBitSet ComponentBitSet;
};


