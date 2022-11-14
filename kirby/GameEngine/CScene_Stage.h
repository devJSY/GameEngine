#pragma once
#include "CScene.h"

class CTexture;
class CAnimation;

class CScene_Stage :
    public CScene
{
private:
    CTexture*           m_TexBackGround;
    CTexture*           m_TexForeGround;
    CAnimation*         m_BackGroundAnim;
    CAnimation*         m_ForeGroundAnim;

    wstring             m_BackGroundPath;
    wstring             m_ForeGroundPath;

    Vec2                m_SceneOffset;

public:
    virtual void update();
    virtual void render(HDC _dc);

    virtual void Enter();
    virtual void Exit();

    void Load(const wstring& _strName);

public:
    CScene_Stage();
    ~CScene_Stage();
};

