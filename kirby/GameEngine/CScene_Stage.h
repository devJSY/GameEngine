#pragma once
#include "CScene.h"

class CScene_Stage :
    public CScene
{
private:

public:
    virtual void update();
    virtual void render(HDC _dc);

    virtual void Enter();
    virtual void Exit();

public:
    CScene_Stage();
    ~CScene_Stage();
};

