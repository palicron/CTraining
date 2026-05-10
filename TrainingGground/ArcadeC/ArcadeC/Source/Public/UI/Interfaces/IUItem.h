#pragma once
#include <vector>

#include "Definitions/UiDefinitions.h"

class IUItem
{
public:
    
    virtual ~IUItem() = default;
    virtual void Draw() = 0;
    virtual void Update() = 0;
    virtual void AddChild(IUItem* Child) = 0;
    virtual void RemoveChild(IUItem* Child) = 0;
    
    virtual std::vector<IUItem*> GetChildren() const = 0;
    
    virtual void SetParent(IUItem* Parent) = 0;
    virtual void Destroy() = 0;
    
    virtual void SetPosition(float x, float y) = 0;
    
    virtual void SetVisibility(const E_Visibility Visibility, const bool bPropagate = false) = 0;
    virtual E_Visibility GetVisibility() const = 0;
    
};
