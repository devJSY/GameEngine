#pragma once
#include "CRoot.h"

class CComponent :
    public CRoot
{

private:
    virtual void Root() = 0;
};

