#include "LMath.h"

Vector2 Vector2::Up = { 0.0f, -1.0f };
Vector2 Vector2::Down = { 0.0f, 1.0f };
Vector2 Vector2::Right = { 1.0f, 0.0f };
Vector2 Vector2::Left = { -1.0f, 0.0f };

Vector2 Vector2::UpRight = { 1.0f, -1.0f };

Vector2 Vector2::UpLeft = { -1.0f, -1.0f };
Vector2 Vector2::DownRight = { 1.0f, 1.0f };
Vector2 Vector2::DownLeft = { -1.0f, 1.0f };

Vector2 Vector2::One = { 1.0f, 1.0f };
Vector2 Vector2::Zero = { 0.0f, 0.0f };

Vector2 Vector2::MoveTowards(Vector2 src, Vector2 dest, float distance)
{
    Vector2 dir = (dest - src).Normalize();
    Vector2 move = dir * distance;
    Vector2 result = src + move;
    float dist = Vector2::Distance(dest, result);
    if (dist <= 20.0f)
        return dest;
    return result;
}
float Vector2::Distance(Vector2 src, Vector2 dest)
{
    float dx = dest.x - src.x;
    float dy = dest.y - src.y;
    return sqrtf(dx * dx + dy * dy);

}

bool Vector2::IsCardinal(Vector2 vect)
{
    if (vect == Vector2::Up || vect == Vector2::Down
        || vect == Vector2::Left || vect == Vector2::Right)
        return true;
    return false;
}

bool Vector2::IsDiagonal(Vector2 vect)
{
    if (vect == Vector2::UpLeft || vect == Vector2::UpRight
        || vect == Vector2::DownLeft || vect == Vector2::DownRight)
        return true;
    return false;
}
