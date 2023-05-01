#pragma once
#include <math.h>
#include "CommonInclude.h"
#define PI 3.141592

struct Vector2
{
    enum class Direction{Up, Down, Left, Right, Zero};

    static Vector2 Up;
    static Vector2 Down;
    static Vector2 Right;
    static Vector2 Left;
    
    static Vector2 UpRight;
    static Vector2 UpLeft;
    static Vector2 DownRight;
    static Vector2 DownLeft;

    static Vector2 One;
    static Vector2 Zero;

    float x;
    float y;

    Vector2()
        :x(0),
        y(0)
    {

    }
    Vector2(float x, float y)
        :x(x),
        y(y)
    {

    }
    Vector2(int x, int y)
        :x((float)x),
        y((float)y)
    {

    }
    // Addition operator overload
    Vector2 operator+(const Vector2& other) const
    {
        float newx = x + other.x;
        float newy = y + other.y;
        return Vector2{ newx, newy };
    }

    // Subtraction operator overload
    Vector2 operator-(const Vector2& other) const
    {
        return Vector2{ x - other.x, y - other.y };
    }

    // Multiplication operator overload (scalar multiplication)
    Vector2 operator*(const float scalar) const
    {
        return Vector2{ x * scalar, y * scalar };
    }

    // Division operator overload (scalar division)
    Vector2 operator/(const float scalar) const
    {
        return Vector2{ x / scalar, y / scalar };
    }

    // Equality operator overload
    bool operator==(const Vector2& other) const
    {
        return x == other.x && y == other.y;
    }

    // Inequality operator overload
    bool operator!=(const Vector2& other) const
    {
        if (x != other.x || y != other.y) return true;
        return false;
    }

    // Compound addition operator overload
    Vector2& operator+=(const Vector2& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    // Compound subtraction operator overload
    Vector2& operator-=(const Vector2& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vector2& operator *=(const float scalar)
    {
        x *= scalar;
        y *= scalar;
        return *this;
    }

    // Prefix increment operator overload
    Vector2& operator++()
    {
        ++x;
        ++y;
        return *this;
    }

    // Postfix increment operator overload
    Vector2 operator++(int)
    {
        Vector2 temp = *this;
        ++(*this);
        return temp;
    }

    // Prefix decrement operator overload
    Vector2& operator--()
    {
        --x;
        --y;
        return *this;
    }

    // Postfix decrement operator overload
    Vector2 operator--(int)
    {
        Vector2 temp = *this;
        --(*this);
        return temp;
    }

    // Negation operator overload
    Vector2 operator-() const
    {
        return Vector2{ -x, -y };
    }

	float Magnitude()
	{
		return sqrtf(x * x + y * y);
	}

	Vector2& Normalize()
	{
		float length = Magnitude();
        if (length == 0)
        {
            x = 0;
            y = 0;
        }
        else {
            x /= length;
            y /= length;
            if (x > 0) x = 1;
            else if (x < 0) x = -1;
            if (y > 0) y = 1;
            else if (y < 0) y = -1;
        }

		return *this;
	}
    Vector2& TileNormalize()
    {
        float length = Magnitude();
        if (length == 0)
        {
            x = 0;
            y = 0;
        }
        else {            
            x /= length;
            y /= length;
            if (x > 0) x = 1; if (x < 0) x = -1;
            if (y > 0) y = 1; if (y < 0) y = -1;
        }
        return *this;
    }

    static Vector2 MoveTowards(Vector2 src, Vector2 dest, float distance);
  
    static float Distance(Vector2 src, Vector2 dest);
    static bool IsCardinal(Vector2 vect);
    static bool IsDiagonal(Vector2 vect);
};

int GetRandomInt(int min, int max)
{
    if (min >= max) return min;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(min, max);
    int randomNumber = distrib(gen);
    return randomNumber;
}

