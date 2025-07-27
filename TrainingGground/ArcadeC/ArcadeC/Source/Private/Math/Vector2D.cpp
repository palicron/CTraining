#include "../../Public/Math/Vector2D.h"

Vector2D::Vector2D()
{
    x=0.f;
    y=0.f;
}

Vector2D::Vector2D(const float x, const float y)
{
    this->x = x;
    this->y = y;
}

Vector2D::Vector2D(const int32_t x, const int32_t y)
{
    this->x = static_cast<float>(x);
    this->y = static_cast<float>(y);
}

Vector2D& Vector2D::operator+=(const Vector2D& other)
{
    x += other.x;
    y += other.y;
    return *this;
}

Vector2D& Vector2D::operator-=(const Vector2D& other)
{
    x -= other.x;
    y -= other.y;
    return *this;
}

Vector2D& Vector2D::operator*=(const Vector2D& other)
{
    x *= other.x;
    y *= other.y;
    return *this;
}

Vector2D& Vector2D::operator/=(const Vector2D& other)
{
    x /= other.x;
    y /= other.y;
    return *this;
}

Vector2D Vector2D::operator+(const Vector2D& V2)
{
    return Vector2D(x + V2.x, y + V2.y);
}

Vector2D Vector2D::operator-(const Vector2D& V2)
{
    return Vector2D(x - V2.x, y - V2.y);
}

Vector2D Vector2D::operator*(const Vector2D& V2)
{
    return Vector2D(x * V2.x, y * V2.y);
}

Vector2D Vector2D::operator/(const Vector2D& V2)
{
    return Vector2D(x / V2.x > 0.f ? V2.x : 1.f, y / V2.y > 0.f ? V2.y : 1.f);
}

Vector2D& Vector2D::operator++(int)
{
    x++;
    y++;
    return *this;
}

std::ostream& Vector2D::operator<<(std::ostream& os)
{
    os << "X: " << x << " " << "Y: " << y;
    return os;
}
