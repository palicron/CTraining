#include "../../Public/Framework/PlayerController.h"
#include "../../Public/Components/MovementComponent.h"
#include <SDL3/SDL.h>
PlayerController::PlayerController()
{
 
}

void PlayerController::Init()
{
    
}

void PlayerController::Update()
{
    switch (Game::Event.type)
    {
    case SDL_EVENT_KEY_DOWN:
        HandleKeyDown(Game::Event.key.key);
        break;
    case SDL_EVENT_KEY_UP:
        break;
    default: ;
    }
}

void PlayerController::PossessPlayer(Entity* TargetPlayer)
{
    PossesPlayer = TargetPlayer;
    if (PossesPlayer)
    {
        PlayerMovementComponent = &PossesPlayer->GetComponent<MovementComponent>();
    }
}

void PlayerController::UnPossessPlayer()
{
    PossesPlayer = nullptr;
    PlayerMovementComponent = nullptr;
}

void PlayerController::HandleKeyDown(const SDL_Keycode KeyDown)
{
    switch (KeyDown)
    {
    case SDLK_W:
        std::printf("Im presiong W\n");
        break;
    case SDLK_A:
        std::printf("Im presiong A\n");
    default: ;
    }
}
