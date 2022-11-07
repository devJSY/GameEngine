#pragma once
#include "CUI.h"

class CBtnUI :
    public CUI
{
private:
    UINT  m_SceneType;

public:
    virtual void start();
    virtual void render(HDC _dc);

public:
    virtual void MouseOn();
    virtual void MouseLbtnDown();
    virtual void MouseLbtnUp();
    virtual void MouseLbtnClicked();

public:
    void SetSceneType(UINT _SceneType) { m_SceneType = _SceneType; }

public:
    CLONE(CBtnUI);

public:
    CBtnUI();
    virtual ~CBtnUI();
};

