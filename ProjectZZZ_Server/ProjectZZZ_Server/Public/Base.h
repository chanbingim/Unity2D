#pragma once

#include "Server_Defines.h"

class CBase
{
protected:
    CBase() = default;
    virtual ~CBase() = default;

public:
    virtual void	Release();

};

