#pragma once
#include "CScene.h"

class CScene_Start :
    public CScene
{
private:

public:
    virtual void update();
    virtual void render(HDC _dc);

    virtual void Enter();
    virtual void Exit();

private:
    virtual void Root() {};

public:
    CScene_Start();
    ~CScene_Start();
};

