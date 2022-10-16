#pragma once
#include "CObject.h"

class Kirby :
    public CObject
{

public:
    virtual void update();
    virtual void render(HDC _dc);

    virtual void OnCollision(CCollider* _pOther);
    virtual void OnCollisionEnter(CCollider* _pOther);
    virtual void OnCollisionExit(CCollider* _pOther);

    CLONE(Kirby);

public:
    Kirby();
    ~Kirby();
};

