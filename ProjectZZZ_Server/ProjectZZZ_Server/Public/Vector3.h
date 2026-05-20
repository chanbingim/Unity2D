#pragma once

struct Vector3
{
    Vector3() : X(0), Y(0), Z(0) {}
    Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
    Vector3(const Vector3& other) : X(other.X), Y(other.Y), Z(other.Z) {}

    static const Vector3 Zero;
    static const Vector3 One;

    Vector3 operator+(const Vector3& other) const {
        return Vector3(X + other.X, Y + other.Y, Z + other.Z);
    }

    Vector3 operator-(const Vector3& other) const {
        return Vector3(X - other.X, Y - other.Y, Z - other.Z);
    }

    Vector3 operator*(const Vector3& other) const {
        return Vector3(X * other.X, Y * other.Y, Z * other.Z);
    }

    Vector3 operator/(const Vector3& other) const {
        return Vector3(X / other.X, Y / other.Y, Z / other.Z);
    }

    Vector3& operator=(const Vector3& other)
    {
        X = other.X;
        Y = other.Y;
        Z = other.Z;
        return *this;
    }

    // Normalize( Unit Vector )
    void        Normalize();
    Vector3     Normalized() const;

    float Get_Length() const { return sqrt(X * X + Y * Y + Z* Z); }
    float Get_SqrtLength() const { return X * X + Y * Y + Z * Z; }

    float X, Y, Z;
};

