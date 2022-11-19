#pragma once
#include "CObject.h"

class CTile :
    public CObject
{
private:
    bool           m_Checked;

public:
    virtual void update();
    virtual void render(HDC _dc);

    virtual void start() {};

public:
    void Checking() { m_Checked = !m_Checked; }
    void CheckingTrue() { m_Checked = true; }
    void CheckingFalse() { m_Checked = false; }

public:
    bool IsChecked() { return m_Checked; }
  

public:
    CLONE(CTile);

private:
    CTile();
    ~CTile();

    friend class CScene_SceneTool;
};

