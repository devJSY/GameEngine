#pragma once
#include "CScene.h"

class CScene_SceneTool :
    public CScene
{
private:

public:
    virtual void update();
    virtual void render(HDC _dc);

    virtual void Enter();
    virtual void Exit();

public:
    CScene_SceneTool();
    ~CScene_SceneTool();
};

