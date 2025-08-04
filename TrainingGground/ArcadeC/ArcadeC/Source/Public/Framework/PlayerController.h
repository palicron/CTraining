#pragma once
#include "../Game.h"
#include "../../Public/Math/Vector2D.h"
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

    Vector2D CurrentVel;
protected:


    Entity* PossesPlayer;
    MovementComponent* PlayerMovementComponent;

    void HandleKeyDown(const SDL_Keycode KeyDown);
    void HandleKeyUP(const SDL_Keycode KeyUp);
};
