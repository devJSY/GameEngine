#pragma once
#include "CObject.h"

class CTile :
    public CObject
{
private:

public:
    virtual void update();
    virtual void render(HDC _dc);

    virtual void start() {};

public:
    CLONE(CTile);

private:
    CTile();
    ~CTile();

    friend class CScene_SceneTool;
};

