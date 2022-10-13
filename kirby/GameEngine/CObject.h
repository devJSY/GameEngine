#pragma once
#include "CRoot.h"

class CObject :
    public CRoot
{
private:
    Vec2 vPos;
    Vec2 vScale;

public:
    void update();
    void render(HDC _dc);

public:
    void SetPos(Vec2 _vPos) { vPos = _vPos; }
    void SetScale(Vec2 _vScale) { vScale = _vScale; }

    Vec2 GetPos() { return vPos; }
    Vec2 GetScale()  { return vScale; }

private:
    virtual void Root() {};

public:
    CObject();
    ~CObject();
};

