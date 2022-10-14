#pragma once
#include "CRoot.h"

class CObject :
    public CRoot
{
private:
    Vec2        vPos;
    Vec2        vScale;
    wstring     m_strName;

public:
    void update();
    void render(HDC _dc);

public:
    void SetPos(Vec2 _vPos) { vPos = _vPos; }
    Vec2 GetPos() { return vPos; }

    void SetScale(Vec2 _vScale) { vScale = _vScale; }
    Vec2 GetScale()  { return vScale; }

    void SetName(const wstring& _strName) { m_strName = _strName; }
    wstring& GetName() { return m_strName; }

private:
    virtual void Root() {};

public:
    CObject();
    ~CObject();
};

