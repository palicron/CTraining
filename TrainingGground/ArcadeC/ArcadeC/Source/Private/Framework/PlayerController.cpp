#include "../../Public/Framework/PlayerController.h"
#include "../../Public/Components/MovementComponent.h"
#include <SDL3/SDL.h>
PlayerController::PlayerController()
{
    CurrentVel = Vector2D::ZeroVector();
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
        HandleKeyUP(Game::Event.key.key);
        break;
    default: ;
    }

    if (PlayerMovementComponent)
    {
        PlayerMovementComponent->Move(CurrentVel);
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
        CurrentVel.y = -1;
        break;
    case SDLK_A:
        CurrentVel.x = -1;
        break;
    case SDLK_S:
        CurrentVel.y = 1;
        break;
    case SDLK_D:
        CurrentVel.x = 1;
        break;
    default: ;
    }

}

void PlayerController::HandleKeyUP(const SDL_Keycode KeyUp)
{
    switch (KeyUp)
    {
    case SDLK_W:
    case SDLK_S:
        CurrentVel.y = 0;
        break;
    case SDLK_D:
    case SDLK_A:
        CurrentVel.x = 0;
        break;
    default: ;
    }
}
