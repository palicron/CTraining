#include "../../Public/UI/UIManager.h"


IUItem* UIManager::AddToViewPort(std::unique_ptr<IUItem> NewItem)
{
    return nullptr;
}

void UIManager::RemoveFromViewPort(IUItem* Item)
{
}

void UIManager::Update()
{
}

void UIManager::Draw()
{
}

void UIManager::UpdateUI()
{
    Update();
    Draw();   
}
