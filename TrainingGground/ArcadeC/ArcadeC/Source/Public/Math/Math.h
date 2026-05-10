#pragma once
#include "Vector2D.h"


//General Class to do Math
class Math
{
public:
    //Clamp de X and Y value of a Vector2D
    static Vector2D ClampVector2DFloat(const Vector2D& Value, const float Min, const float Max);
    static Vector2D NormalizeVector2D(const Vector2D& Value);
    static Vector2D NormalizeVector2DAndClamp(const Vector2D& Value, const float Min, const float Max);
    
};
