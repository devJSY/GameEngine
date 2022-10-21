#pragma once
#include "CUI.h"
class CBtnUI :
    public CUI
{

public:
    virtual void start();

public:
    virtual void MouseOn();
    virtual void MouseLbtnDown();
    virtual void MouseLbtnUp();
    virtual void MouseLbtnClicked();

public:
    CLONE(CBtnUI);

public:
    CBtnUI();
    virtual ~CBtnUI();
};

