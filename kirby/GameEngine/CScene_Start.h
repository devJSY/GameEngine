#pragma once
#include "CScene.h"

class CScene_Start :
    public CScene
{
private:
    CTexture* m_TexBackGround;

public:
    virtual void update();
    virtual void render(HDC _dc);

    virtual void Enter();
    virtual void Exit();

public:
    CScene_Start();
    ~CScene_Start();
};

