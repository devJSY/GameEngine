#pragma once
#include "CScene.h"

class CScene_Animation_Tool :
    public CScene
{
private:

public:
    virtual void update();
    virtual void render(HDC _dc);

    virtual void Enter();
    virtual void Exit();

public:
    CScene_Animation_Tool();
    ~CScene_Animation_Tool();
};

