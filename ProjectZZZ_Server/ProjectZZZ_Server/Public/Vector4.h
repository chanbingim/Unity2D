#pragma once

struct Vector4
{
    Vector4() : X(0), Y(0), Z(0), W(0) {}
    Vector4(float x, float y, float z, float w) : X(x), Y(y), Z(z), W(w) {}
    Vector4(const Vector4& other) : X(other.X), Y(other.Y), Z(other.Z), W(other.W) {}

    static const Vector4 Zero;
    static const Vector4 One;

    Vector4 operator+(const Vector4& other) const {
        return Vector4(X + other.X, Y + other.Y, Z + other.Z, W + other.W);
    }

    Vector4 operator-(const Vector4& other) const {
        return Vector4(X - other.X, Y - other.Y, Z - other.Z, W - other.W);
    }

    Vector4 operator*(const Vector4& other) const {
        return Vector4(X * other.X, Y * other.Y, Z * other.Z, W * other.W);
    }

    Vector4 operator/(const Vector4& other) const {
        return Vector4(X / other.X, Y / other.Y, Z / other.Z, W / other.W);
    }

    Vector4& operator=(const Vector4& other)
    {
        X = other.X;
        Y = other.Y;
        Z = other.Z;
        W = other.W;
        return *this;
    }

    // Normalize( Unit Vector )
    void        Normalize();
    Vector4     Normalized() const;

    float Get_Length() const { return sqrt(X * X + Y * Y + Z * Z + W * W); }
    float Get_SqrtLength() const { return X * X + Y * Y + Z * Z + W* W; }

    float X, Y, Z, W;
};

