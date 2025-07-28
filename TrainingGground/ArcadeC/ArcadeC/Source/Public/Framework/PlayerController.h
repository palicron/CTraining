#pragma once
#include "../Game.h"
#include "EntityComponentSystem.h"

class MovementComponent;

class PlayerController 
{
    
public:
    
    PlayerController();
    ~PlayerController() = default;

    void Init();
    void Update();
    void PossessPlayer(Entity* TargetPlayer);
    void UnPossessPlayer();
    
protected:


    Entity* PossesPlayer;
    MovementComponent* PlayerMovementComponent;

    void HandleKeyDown(const SDL_Keycode KeyDown);
    
};
