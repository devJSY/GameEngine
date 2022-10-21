#pragma once
#include "CUI.h"
class CPanelUI :
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
    CLONE(CPanelUI);

public:
    CPanelUI();
    virtual ~CPanelUI();
};

