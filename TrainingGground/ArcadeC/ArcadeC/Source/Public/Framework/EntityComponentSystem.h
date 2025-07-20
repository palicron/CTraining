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
using ComponentArray = std::array< Component*, maxComponents>;

class Component
{
public:
    
    Component() = default;
    virtual ~Component() = default;

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
            
        }
    }

    void Draw()
    {
        for (auto& Component : Components)
        {
            Component->ComponentDraw();
            
        }
    }

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
        //Old Implematation
        /*T* c(new T(std::forward<TArgs>(mArgs)...));
        c->SetOwner(this);
        std::unique_ptr<Component> uPTr(c);
        Components.emplace_back(std::move(uPTr));
        ComponentArray[GetComponentTypeID<T>()] = c;
        ComponentBitSet[GetComponentTypeID<T>()] = true;
        c->ComponentInit();
        return *c;*/

        //Implementin using Moder c++, creating the unique to not need to warp it 
        std::unique_ptr<T> c = std::make_unique<T>(std::forward<TArgs>(mArgs)...);
        T* RawPtr = c.get();
        RawPtr->SetOwner(this);
        c->ComponentInit();
        Components.emplace_back(std::move(c));
        ComponentArray[GetComponentTypeID<T>()] = RawPtr;
        ComponentBitSet[GetComponentTypeID<T>()] = true;
        
        return *RawPtr;
    }

    template<typename T> T& GetComponent() const
    {
        return *static_cast<T*>(ComponentArray[GetComponentTypeID<T>()]);
    }
private:
    
    bool bActive = true;

    std::vector<std::unique_ptr<Component>> Components;

    ComponentArray ComponentArray;

    ComponentBitSet ComponentBitSet;
};

class EntityManager
{

public:
    void update()
    {
        //@TODO: not all eneties shoudl be update ther shoudl be ones that only render
        for (std::unique_ptr<Entity>& Entity : Entities)
        {
            Entity->update();
        }
    }

    void Draw()
    {
        //@TODO: not all eneties shoudl be Draw only Entities that has render components
        for (std::unique_ptr<Entity>& Entity : Entities)
        {
            Entity->Draw();
        }
    }

    void refresh()
    {
        Entities.erase(std::remove_if(std::begin(Entities), std::end(Entities), [](const std::unique_ptr<Entity>& InEntity)
        {
            return !InEntity->IsActive();
        }));
    }

    Entity& CreateEntity()
    {
        std::unique_ptr<Entity> NewEntity = std::make_unique<Entity>();
        Entity* RawPtr = NewEntity.get();
        Entities.emplace_back(std::move(NewEntity));
        return *RawPtr;
    }
    
private:
    std::vector<std::unique_ptr<Entity>> Entities;
};


