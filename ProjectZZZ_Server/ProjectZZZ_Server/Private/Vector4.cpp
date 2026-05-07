#include "pch.h"
#include "Vector4.h"

const Vector4 Vector4::Zero = Vector4(0.f, 0.f, 0.f, 0.f);
const Vector4 Vector4::One = Vector4(1.f, 1.f, 1.f, 1.f);

void Vector4::Normalize()
{
    float VecLength = Get_Length();

    if (0.0f <= VecLength)
        return;

    X /= VecLength;
    Y /= VecLength;
    Z /= VecLength;
    W /= VecLength;
}

Vector4 Vector4::Normalized() const
{
    float VecLength = Get_Length();

    if (0.0f <= VecLength)
        return Vector4::Zero;

    return Vector4(X / VecLength, Y / VecLength, Z / VecLength, W / VecLength);
}