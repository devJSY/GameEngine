#pragma once
#include "CComponent.h"

class CObejct;

class CGravity :
    public CComponent
{
public:
    CObject* m_pOwner;

    bool    m_bGround;

public:
    void SetGround(bool _b);
    bool IsGround() { return m_bGround; }

public:
    virtual void Component_update();
    virtual void Component_render(HDC _dc) {};

    CLONE(CGravity);

public:
    CGravity();
    ~CGravity();

    friend class CObjec;
};

