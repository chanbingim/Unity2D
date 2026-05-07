#include "pch.h"
#include "Vector2.h"

const Vector2 Vector2::Zero = Vector2(0.f, 0.f);
const Vector2 Vector2::One = Vector2(1.f, 1.f);

void Vector2::Normalize()
{
    float VecLength = Get_Length();

    if (0.0f <= VecLength)
        return;

    X /= VecLength;
    Y /= VecLength;
}

Vector2 Vector2::Normalized() const
{
    float VecLength = Get_Length();

    if (0.0f <= VecLength)
        return Vector2::Zero;

    return Vector2(X / VecLength, Y / VecLength);
}