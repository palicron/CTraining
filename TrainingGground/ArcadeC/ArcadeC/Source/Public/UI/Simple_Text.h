#pragma once
#include <string>

#include "Interfaces/IUItem.h"

class Simple_Text: public IUItem
{
public:
    
    Simple_Text();
    ~Simple_Text() override = default;
    
    void Draw() override;
    void Update() override;
    
    void AddChild(IUItem* Child) override;
    void RemoveChild(IUItem* Child) override;
    
    std::vector<IUItem*> GetChildren() const override;
    
    
    void SetParent(IUItem* NewParent) override;
    IUItem* GetParent() const override;
    void Destroy() override;
    
    void SetPosition(float x, float y) override;
    
    void SetVisibility(const E_Visibility NewVisibility, const bool bPropagate = false) override;
    E_Visibility GetVisibility() const override;
    
    void SetText(const std::string& NewText);
    
    const std::string& GetText() const
    {
        return Text;
    }
    
private:
    
    std::string Text;
    
    E_Visibility Visibility;
    
    IUItem* Parent;
    
    std::vector<IUItem*> Children;
    
    
    
};
