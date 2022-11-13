#pragma once
#include "CScene.h"

class CTexture;
class CAnimation;

class CScene_SceneTool :
    public CScene
{
private:
    CTexture*                m_TexBackGround;
    vector<CTexture*>        m_vTexForeGround;
    CAnimation*              m_BackGroundAnim;
    CAnimation*              m_ForeGroundAnim;

    Vec2                     m_SceneOffset;


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
    CTexture* GetForeGroundTex(int _idx) 
    { 
        if (0 == m_vTexForeGround.size())
        {
            return nullptr;
        }

        return m_vTexForeGround[_idx]; 
    }
    CAnimation* GetBackGroundAnim() { return m_BackGroundAnim; }
    CAnimation* GetForeGroundAnim() { return m_ForeGroundAnim; }


public:
    CScene_SceneTool();
    ~CScene_SceneTool();
};

