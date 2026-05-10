#include "../../Public/UI/UIManager.h"
#include <SDL3/SDL.h>
#include <SDL3_ttf/SDL_ttf.h>

IUItem* UIManager::AddToViewPort(std::unique_ptr<IUItem> NewItem)
{
    return nullptr;
}

void UIManager::RemoveFromViewPort(IUItem* Item)
{
}

void UIManager::InitUIManager()
{
    if (!TTF_Init()) {
        SDL_Log("Couldn't initialize SDL_ttf: %s\n", SDL_GetError());
    	SDL_APP_FAILURE;
        return;
    }

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
