#pragma once
#include "CScene.h"

class CTexture;
class CAnimation;

class CScene_SceneTool :
    public CScene
{
private:
    CTexture*        m_BackGround;
    CTexture*        m_ForeGround;
    CAnimation*     m_BackGroundAnim;
    CAnimation*     m_ForeGroundAnim;





public:
    virtual void update();
    virtual void render(HDC _dc);

    virtual void Enter();
    virtual void Exit();

public:
    void LoadBackGround();
    void LoadForeGround();

public:
    CScene_SceneTool();
    ~CScene_SceneTool();
};

