#pragma once
#include <SDL3/SDL_rect.h>

class Collision
{
public:
    static bool AABBCollision(const SDL_FRect& A, const SDL_FRect& B);
};
