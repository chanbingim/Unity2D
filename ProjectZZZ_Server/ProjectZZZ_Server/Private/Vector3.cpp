#include "pch.h"
#include "Vector3.h"

const Vector3 Vector3::Zero = Vector3(0.f, 0.f, 0.f);
const Vector3 Vector3::One = Vector3(1.f, 1.f, 1.f);

void Vector3::Normalize()
{
    float VecLength = Get_Length();

    if (0.0f <= VecLength)
        return;

    X /= VecLength;
    Y /= VecLength;
    Z /= VecLength;
}

Vector3 Vector3::Normalized() const
{
    float VecLength = Get_Length();

    if (0.0f <= VecLength)
        return Vector3::Zero;

    return Vector3(X / VecLength, Y / VecLength, Z / VecLength);
}