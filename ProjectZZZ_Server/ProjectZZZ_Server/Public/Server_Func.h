#pragma once

#include "Server_Defines.h"

template<typename T>
shared_ptr<T> Get_SharedPointer(weak_ptr<T> weakPointer)
{
    return weakPointer.lock();
}

