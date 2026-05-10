#pragma once
#include "Interfaces/IUItem.h"

class Simple_Text: public IUItem
{
public:
    
    Simple_Text();
    ~Simple_Text() override;
    
    void Draw() override;
    void Update() override;
    
    void AddChild(IUItem* Child) override;
    void RemoveChild(IUItem* Child) override;
    
    std::vector<IUItem*> GetChildren() const override;
    
    void SetParent(IUItem* Parent) override;
    void Destroy() override;
    
    void SetPosition(float x, float y) override;
    
    void SetVisibility(const E_Visibility Visibility, const bool bPropagate = false) override;
    E_Visibility GetVisibility() const override;
    
};
