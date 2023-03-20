#include "LMath.h"

Vector2 Vector2::Up = { 0.0f, -1.0f };
Vector2 Vector2::Down = { 0.0f, 1.0f };
Vector2 Vector2::Right = { 1.0f, 0.0f };
Vector2 Vector2::Left = { -1.0f, 0.0f };


Vector2 Vector2::One = { 1.0f, 1.0f };
Vector2 Vector2::Zero = { 0.0f, 0.0f };

Vector2 Vector2::MoveTowards(Vector2 src, Vector2 dest, float distance)
{
    Vector2 dir = (dest - src).Normalize();
    Vector2 move = dir * distance;
    Vector2 result = src + move;
    float dist = Vector2::Distance(dest, result);
    if (dist < 0.01f)
        return dest;
    return result;
}
float Vector2::Distance(Vector2 src, Vector2 dest)
{
    float dx = dest.x - src.x;
    float dy = dest.y - src.y;
    return sqrtf(dx * dx + dy * dy);

}