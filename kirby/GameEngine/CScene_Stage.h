#pragma once
#include "CScene.h"

class CTexture;
class CAnimation;

class CScene_Stage :
    public CScene
{
private:
    tStageConf         m_tStageConf;

public:
    virtual void update();
    virtual void render(HDC _dc);

    virtual void Enter();
    virtual void Exit();

    void Load(const wstring& _strName);

public:
    CTexture* GetBackGroundTex() { return m_tStageConf.TexBackGround; }
    CTexture* GetForeGroundTex() { return m_tStageConf.TexForeGround; }
    CAnimation* GetBackGroundAnim() { return m_tStageConf.BackGroundAnim; }
    CAnimation* GetForeGroundAnim() { return m_tStageConf.ForeGroundAnim; }

public:
    CScene_Stage();
    ~CScene_Stage();
};

