#include "../Public/Collision.h"

bool Collision::AABBCollision(const SDL_FRect& A, const SDL_FRect& B)
{
    if (A.w <= 0 || A.h <= 0 || B.w <= 0 || B.h <= 0)
    {
        return false;
    }

    if ((A.x + A.w >= B.x) &&
        (B.x + B.w >= A.x) &&
        (A.y + A.h >= B.y) &&
        (B.y + B.h >= A.y))
    {
        return true;
    }

    return false;
}
