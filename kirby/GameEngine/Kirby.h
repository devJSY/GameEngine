#pragma once
#include "CObject.h"

class Kirby :
    public CObject
{

public:
    virtual void update();
    virtual void render(HDC _dc);

public:
    Kirby();
    ~Kirby();

private:
    virtual void Root() {};
};

