#pragma once

struct Vector2
{
    Vector2() : X(0), Y(0) {}
    Vector2(float x, float y) : X(x), Y(y) {}
    Vector2(const Vector2& other) : X(other.X), Y(other.Y) {}

    static const Vector2 Zero;
    static const Vector2 One;

    Vector2 operator+(const Vector2& other) const {
        return Vector2( X + other.X, Y + other.Y);
    }

    Vector2 operator-(const Vector2& other) const {
        return Vector2(X - other.X, Y - other.Y);
    }

    Vector2 operator*(const Vector2& other) const {
        return Vector2(X * other.X, Y * other.Y);
    }

    Vector2 operator/(const Vector2& other) const {
        return Vector2(X / other.X, Y / other.Y);
    }

    Vector2 operator=(const Vector2& other) const {
        return Vector2(other);
    }

    // Normalize( Unit Vector )
    void        Normalize();
    Vector2     Normalized() const;

    float Get_Length() const { return sqrt(X * X + Y * Y); }
    float Get_SqrtLength() const { return X * X + Y * Y; }

    float X, Y;
};

