#pragma once
#include "CRoot.h"
#include "global.h"

class CObject;

class CComponent :
    public CRoot
{
private:
    CObject*    m_pOwner;

public:
    virtual void Component_update() = 0;
    virtual void Component_render(HDC _dc) = 0;

public:
    CObject* GetOwner() { return m_pOwner; }

public:
    virtual CComponent* Clone() = 0;

public:
    CComponent();
    CComponent(const CComponent& _origin);
    virtual ~CComponent();

    friend class CObject;
};

