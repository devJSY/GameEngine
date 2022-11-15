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
    CScene_Stage();
    ~CScene_Stage();
};

