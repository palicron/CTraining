#include "../../Public/Math/Math.h"
#include <algorithm>

Vector2D Math::ClampVector2DFloat(const Vector2D& Value, const float Min, const float Max)
{
    Vector2D NewVector;
    NewVector.x = std::clamp(Value.x, Min, Max);
    NewVector.y = std::clamp(Value.y, Min, Max);
    return NewVector;
}

Vector2D Math::NormalizeVector2D(const Vector2D& Value)
{
    const float Vectorlength = sqrt(Value.x * Value.x + Value.y * Value.y);

    if (Vectorlength == 0.f)
    {
        return Vector2D::ZeroVector();
    }
    return Vector2D(Value.x / Vectorlength, Value.y / Vectorlength);
}

Vector2D Math::NormalizeVector2DAndClamp(const Vector2D& Value, const float Min, const float Max)
{
    return NormalizeVector2D(ClampVector2DFloat(Value, Min, Max));
}
