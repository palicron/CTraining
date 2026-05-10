#pragma once
#include <memory>
#include <vector>
#include "../Public/UI/Interfaces/IUItem.h"
class IUItem;

class UIManager
{
public:
    
    static IUItem* AddToViewPort(std::unique_ptr<IUItem> NewItem);
    
    static void RemoveFromViewPort(IUItem* Item);

    void InitUIManager();
    
    void Update();
    
    void Draw();
    
    void UpdateUI();

    
private:
    
    std::vector<std::unique_ptr<IUItem>> RegisterUi;
};
