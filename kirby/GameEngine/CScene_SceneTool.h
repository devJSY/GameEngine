#pragma once
#include "CScene.h"

class CTexture;
class CAnimation;

class CScene_SceneTool :
    public CScene
{
private:
    CTexture*                m_TexBackGround;
    CTexture*                m_TexForeGround;
    CAnimation*              m_BackGroundAnim;
    CAnimation*              m_ForeGroundAnim;

    wstring                 m_BackGroundPath;
    wstring                 m_ForeGroundPath;

    Vec2                     m_SceneOffset;

    Vec2                    vPrevMousePos;

public:
    virtual void update();
    virtual void render(HDC _dc);

    virtual void Enter();
    virtual void Exit();

public:
    void LoadBackGround();
    void LoadForeGround();

public:
    CTexture* GetBackGroundTex() { return m_TexBackGround; }
    CTexture* GetForeGroundTex() { return m_TexForeGround; }
    CAnimation* GetBackGroundAnim() { return m_BackGroundAnim; }
    CAnimation* GetForeGroundAnim() { return m_ForeGroundAnim; }

public:
    void Save(const wstring& _strName);
    void Load(const wstring& _strName);


public:
    CScene_SceneTool();
    ~CScene_SceneTool();
};

