#pragma once
#include "CObject.h"

class CTexture;

class Kirby :
    public CObject
{
    CTexture* m_pTex;

public:
    virtual void update();
    virtual void render(HDC _dc);
    virtual void start();

    virtual void OnCollision(CCollider* _pOther);
    virtual void OnCollisionEnter(CCollider* _pOther);
    virtual void OnCollisionExit(CCollider* _pOther);

    CLONE(Kirby);

public:
    Kirby();
    virtual ~Kirby();
};

