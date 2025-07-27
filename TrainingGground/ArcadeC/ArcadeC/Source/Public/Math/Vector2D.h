#pragma once
#include <cstdint>
#include <iostream>
class Vector2D
{
public:

    Vector2D();
    Vector2D(const float x, const float y);
    Vector2D(const int32_t x, const int32_t y);
    ~Vector2D() = default;
    float x;
    float y;

    static Vector2D ZeroVector() { return Vector2D();}

    Vector2D& operator+=(const Vector2D& other);
    Vector2D& operator-=(const Vector2D& other);
    Vector2D& operator*=(const Vector2D& other);
    Vector2D& operator/=(const Vector2D& other);

    Vector2D operator+(const Vector2D& V2);
    Vector2D operator-(const Vector2D& V2);
    Vector2D operator*(const Vector2D& V2);
    Vector2D operator/(const Vector2D& V2);

    Vector2D& operator++(int);

    std::ostream& operator<<(std::ostream& os);
};


